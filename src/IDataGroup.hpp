// IDataRange.hpp

#ifndef IDATAGROUP_HPP_
#define IDATAGROUP_HPP_

#include <memory>

class IDataGroup
{
public:
	virtual ~IDataGroup() = default;

	// Set the frequency
	virtual void setFrequency(double frequency) = 0;

	// Set the cumulative frequency
	virtual void setCumulativeFrequency(double cumulativeFrequency) = 0;

	// Get the lower bound
	virtual double getLowerBound() const = 0;

	// Get the upper bound
	virtual double getUpperBound() const = 0;

	// Get the smooth lower bound
	virtual double getSmoothLowerBound() const = 0;

	// Get the smooth upper bound
	virtual double getSmoothUpperBound() const = 0;

	// Get the midpoint
	virtual double getMidpoint() const = 0;

	// Get the frequency
	virtual double getFrequency() const = 0;

	// Get the cumulative frequency
	virtual double getCumulativeFrequency() const = 0;

	// Get the maximum number of decimal places
	virtual int getPrecision() const = 0;

	// Create a copy of this object
	virtual std::unique_ptr<IDataGroup> clone() const = 0;

	// Estimate and create the next logical data group
	// This will return a new DataGroup with the following properties:
	//  - The class width remains the same
	//  - The lower and upper bounds are incremented by the class width
	//  - The frequency is set by the function input
	//  - The cumulative frequency is deduced implicitly
	//  - The precision is deduced implicitly
	virtual std::unique_ptr<IDataGroup> stack(double frequency) const = 0;
};

#endif /* IDATAGROUP_HPP_ */
