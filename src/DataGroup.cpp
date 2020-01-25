// DataRange.cpp

#include "DataGroup.hpp"

#include <cassert>
#include <cmath>

DataGroup::DataGroup(double lowerBound, double upperBound, int precision) :
	lowerBound(lowerBound),
	upperBound(upperBound),
	frequency(0.0),
	cumulativeFrequency(0.0),
	precision(precision)
{
	assert(precision >= 0);
	assert(lowerBound <= upperBound);
}

DataGroup::DataGroup(double lowerBound, double upperBound, double frequency,
		double cumulativeFrequency, int precision) :
		lowerBound(lowerBound),
		upperBound(upperBound),
		frequency(frequency),
		cumulativeFrequency(cumulativeFrequency),
		precision(precision)
{
	assert(precision >= 0);
	assert(lowerBound <= upperBound);
}

void DataGroup::setFrequency(double frequency)
{
	this->frequency = frequency;
}

void DataGroup::setCumulativeFrequency(double cumulativeFrequency)
{
	this->cumulativeFrequency = cumulativeFrequency;
}

double DataGroup::getLowerBound() const
{
	return lowerBound;
}

double DataGroup::getUpperBound() const
{
	return upperBound;
}

double DataGroup::getSmoothLowerBound() const
{
	return lowerBound - 5 / std::pow(10, precision + 1);
}

double DataGroup::getSmoothUpperBound() const
{
	return upperBound + 5 / std::pow(10, precision + 1);
}

double DataGroup::getMidpoint() const
{
	return (upperBound + lowerBound) / 2.0;
}

double DataGroup::getFrequency() const
{
	return frequency;
}

double DataGroup::getCumulativeFrequency() const
{
	return cumulativeFrequency;
}

int DataGroup::getPrecision() const
{
	return precision;
}

std::unique_ptr<IDataGroup> DataGroup::clone() const
{
	return std::unique_ptr<IDataGroup>(new DataGroup(
			getLowerBound(),
			getUpperBound(),
			getFrequency(),
			getCumulativeFrequency(),
			getPrecision()
	));
}

std::unique_ptr<IDataGroup> DataGroup::stack(double frequency) const
{
	double classWidth = getUpperBound() + std::pow(10, -getPrecision()) - getLowerBound();

	return std::unique_ptr<IDataGroup>(new DataGroup(
			getLowerBound() + classWidth,
			getUpperBound() + classWidth,
			frequency,
			getCumulativeFrequency() + frequency,
			getPrecision()
	));
}

RelativeDataGroup::RelativeDataGroup(double lowerBound, double upperBound,
		int precision, int size) :
		DataGroup(lowerBound, upperBound, precision),
		size(size)
{
	assert(size > 0);
}

RelativeDataGroup::RelativeDataGroup(double lowerBound, double upperBound,
		double frequency, double cumulativeFrequency, int precision, int size) :
		DataGroup(lowerBound, upperBound, frequency, cumulativeFrequency, precision),
		size(size)
{
	assert(size > 0);
}

double RelativeDataGroup::getFrequency() const
{
	return DataGroup::getFrequency() / getSize();
}

double RelativeDataGroup::getCumulativeFrequency() const
{
	return DataGroup::getCumulativeFrequency() / getSize();
}

int RelativeDataGroup::getSize() const
{
	return size;
}

std::unique_ptr<IDataGroup> RelativeDataGroup::clone() const
{
	return std::unique_ptr<IDataGroup>(new RelativeDataGroup(
			getLowerBound(),
			getUpperBound(),
			DataGroup::getFrequency(),
			DataGroup::getCumulativeFrequency(),
			getPrecision(),
			getSize()
	));
}

std::unique_ptr<IDataGroup> RelativeDataGroup::stack(double frequency) const
{
	double classWidth = getUpperBound() + std::pow(10, -getPrecision()) - getLowerBound();

	return std::unique_ptr<IDataGroup>(new RelativeDataGroup(
			getLowerBound() + classWidth,
			getUpperBound() + classWidth,
			frequency,
			DataGroup::getCumulativeFrequency() + frequency,
			getPrecision(),
			getSize()
	));
}

PercentageDataGroup::PercentageDataGroup(double lowerBound, double upperBound,
		int precision, int size) :
		RelativeDataGroup(lowerBound, upperBound, precision, size)
{
}

PercentageDataGroup::PercentageDataGroup(double lowerBound, double upperBound,
		double frequency, double cumulativeFrequency, int precision, int size) :
		RelativeDataGroup(lowerBound, upperBound, frequency, cumulativeFrequency,
				precision, size)
{
}

double PercentageDataGroup::getFrequency() const
{
	return RelativeDataGroup::getFrequency() * 100;
}

double PercentageDataGroup::getCumulativeFrequency() const
{
	return RelativeDataGroup::getCumulativeFrequency() * 100;
}

std::unique_ptr<IDataGroup> PercentageDataGroup::clone() const
{
	return std::unique_ptr<IDataGroup>(new PercentageDataGroup(
			getLowerBound(),
			getUpperBound(),
			DataGroup::getFrequency(),
			DataGroup::getCumulativeFrequency(),
			getPrecision(),
			getSize()
	));
}

std::unique_ptr<IDataGroup> PercentageDataGroup::stack(double frequency) const
{
	double classWidth = getUpperBound() + std::pow(10, -getPrecision()) - getLowerBound();

	return std::unique_ptr<IDataGroup>(new PercentageDataGroup(
			getLowerBound() + classWidth,
			getUpperBound() + classWidth,
			frequency,
			DataGroup::getCumulativeFrequency() + frequency,
			getPrecision(),
			getSize()
	));
}
