// IDataCollection.hpp

#ifndef IDATACOLLECTION_HPP_
#define IDATACOLLECTION_HPP_

#include <functional>
#include <memory>
#include <vector>

#include "IDataGroup.hpp"

enum class FrequencyStyle : int
{
	RAW,
	RELATIVE,
	PERCENTAGE
};

class IDataCollection
{
public:
	virtual ~IDataCollection() = default;

	// Add a value to the collection
	virtual void insert(double value) = 0;

	// Apply a non-modifying function to each element
	virtual void forEach(const std::function<void(double)>& f) const = 0;

	// Get the minimum data value
	virtual double getMin() const = 0;

	// Get the maximum data value
	virtual double getMax() const = 0;

	// Get the range
	virtual double getRange() const = 0;

	// Get the median
	virtual double getMedian() const = 0;

	// Get the mean
	virtual double getMean() const = 0;

	// Count data values in the interval [lowerBound, upperBound]
	virtual double getFrequency(double lowerBound, double upperBound) const = 0;

	// Get the maximum amount of decimal places
	virtual int getPrecision() const = 0;

	// Get the total number of elements
	virtual int getSize() const = 0;

	// Organize into k number of DataGroups
	virtual std::vector<std::unique_ptr<IDataGroup>> group(int k, FrequencyStyle style) const = 0;
};

#endif /* IDATACOLLECTION_HPP_ */
