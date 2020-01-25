// DataRange.hpp

#ifndef DATAGROUP_HPP_
#define DATAGROUP_HPP_

#include "IDataGroup.hpp"

class DataGroup : public IDataGroup
{
public:
	DataGroup(double lowerBound, double upperBound, int precision);
	DataGroup(double lowerBound, double upperBound,
			double frequency, double cumulativeFrequency,
			int precision);

	void setFrequency(double frequency) override;
	void setCumulativeFrequency(double cumulativeFrequency) override;

	double getLowerBound() const override;
	double getUpperBound() const override;
	double getSmoothLowerBound() const override;
	double getSmoothUpperBound() const override;
	double getMidpoint() const override;
	double getFrequency() const override;
	double getCumulativeFrequency() const override;
	int getPrecision() const override;

	std::unique_ptr<IDataGroup> clone() const override;
	std::unique_ptr<IDataGroup> stack(double frequency) const override;

private:
	double lowerBound;
	double upperBound;
	double frequency;
	double cumulativeFrequency;
	int precision;
};

class RelativeDataGroup : public DataGroup
{
public:
	RelativeDataGroup(double lowerBound, double upperBound, int precision, int size);
	RelativeDataGroup(double lowerBound, double upperBound,
				double frequency, double cumulativeFrequency,
				int precision, int size);

	double getFrequency() const override;
	double getCumulativeFrequency() const override;
	int getSize() const;

	std::unique_ptr<IDataGroup> clone() const override;
	std::unique_ptr<IDataGroup> stack(double frequency) const override;

private:
	int size;
};

class PercentageDataGroup : public RelativeDataGroup
{
public:
	PercentageDataGroup(double lowerBound, double upperBound, int precision, int size);
	PercentageDataGroup(double lowerBound, double upperBound,
				double frequency, double cumulativeFrequency,
				int precision, int size);

	double getFrequency() const override;
	double getCumulativeFrequency() const override;

	std::unique_ptr<IDataGroup> clone() const override;
	std::unique_ptr<IDataGroup> stack(double frequency) const override;
};

#endif /* DATAGROUP_HPP_ */
