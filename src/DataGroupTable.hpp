// GroupedData.hpp

#ifndef DATAGROUPTABLE_HPP_
#define DATAGROUPTABLE_HPP_

#include <functional>
#include <memory>
#include <vector>

#include "IDataCollection.hpp"
#include "IDataGroup.hpp"

class DataGroupTable
{
public:
	DataGroupTable() = delete;

	// Create a data table with a single starting data group
	DataGroupTable(const IDataGroup& startingGroup);

	// Create a data table by grouping existing data in a collection
	DataGroupTable(const IDataCollection& collection, int k,
			FrequencyStyle style = FrequencyStyle::RAW);

	// Create the next logical data group and set its frequency
	void insert(double frequency);

	// Apply a non-modifying function to each data group
	void forEach(const std::function< void(const IDataGroup&) >& f) const;

private:
	std::vector<std::unique_ptr<IDataGroup>> ranges;
};

#endif /* DATAGROUPTABLE_HPP_ */
