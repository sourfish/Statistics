// DataCollection.cpp

#include "DataCollection.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <memory>
#include <numeric>
#include <vector>

#include "DataGroup.hpp"

DataCollection::DataCollection() :
		sum(0.0)
{
}

DataCollection::DataCollection(const std::vector<double>& values) :
		values(values)
{
	std::sort(this->values.begin(), this->values.end());
	sum = std::accumulate(this->values.begin(), this->values.end(), 0.0);
}

void DataCollection::insert(double value)
{
	values.push_back(value);
	std::sort(values.begin(), values.end());
	sum += value;
}

void DataCollection::forEach(const std::function<void(double)>& f) const
{
	for (auto value : values)
	{
		f(std::move(value));
	}
}

double DataCollection::getMin() const
{
	assert(!values.empty());
	return values.front();
}

double DataCollection::getMax() const
{
	assert(!values.empty());
	return values.back();
}

double DataCollection::getRange() const
{
	assert(!values.empty());
	return getMax() - getMin();
}

double DataCollection::getMedian() const
{
	assert(!values.empty());
	return (getMin() + getMax()) / 2.0;
}

double DataCollection::getMean() const
{
	assert(!values.empty());
	return sum / getSize();
}

double DataCollection::getFrequency(double lowerBound, double upperBound) const
{
	double frequency = 0.0;

	for (auto value : values)
	{
		if (lowerBound <= value && value <= upperBound)
		{
			++frequency;
		}
	}

	return frequency;
}

int DataCollection::getPrecision() const
{
	int precision = 0;

	for (auto value : values)
	{
		double newPrecision = getPrecision(value);
		if (newPrecision > precision)
		{
			precision = newPrecision;
		}
	}

	return precision;
}

int DataCollection::getSize() const
{
	return values.size();
}

std::vector<std::unique_ptr<IDataGroup>> DataCollection::group(int k, FrequencyStyle style) const
{
	assert(!values.empty());
	assert(k > 0);

	int precision = getPrecision();
	double classWidth = roundUp(getRange() / k, precision);
	double cumulativeFrequency;

	std::vector<std::unique_ptr<IDataGroup>> ranges;
	for (int i = 0; i < k; ++i)
	{
		double lowerBound = getMin() + classWidth * i;
		double upperBound = lowerBound + classWidth - std::pow(10, -precision);
		double frequency = getFrequency(lowerBound, upperBound);
		cumulativeFrequency += frequency;

		switch (style)
		{
		case FrequencyStyle::RAW:
			ranges.emplace_back(new DataGroup(
					lowerBound, upperBound,
					frequency, cumulativeFrequency,
					precision
			));
			break;

		case FrequencyStyle::RELATIVE:
			ranges.emplace_back(new RelativeDataGroup(
					lowerBound, upperBound,
					frequency, cumulativeFrequency,
					precision,
					getSize()
			));
			break;

		case FrequencyStyle::PERCENTAGE:
			ranges.emplace_back(new PercentageDataGroup(
					lowerBound, upperBound,
					frequency, cumulativeFrequency,
					precision,
					getSize()
			));
			break;

		default:
			assert(false);
		}
	}

	return ranges;
}

int DataCollection::getPrecision(double value)
{
	for (int i = 0; i < 12; ++i)
	{
		double multiplied = value * std::pow(10, i);
		if (multiplied == static_cast<int>(multiplied))
		{
			return i;
		}
	}

	return 12;
}

double DataCollection::roundUp(double value, int precision)
{
	double multiplied = value * std::pow(10, precision);
	multiplied = static_cast<int>(multiplied) + 1;
	multiplied /= std::pow(10, precision);
	return multiplied;
}
