// GroupedData.cpp

#include "DataGroupTable.hpp"

DataGroupTable::DataGroupTable(const IDataGroup& startingGroup)
{
	ranges.push_back(std::move(startingGroup.clone()));
}

DataGroupTable::DataGroupTable(const IDataCollection& collection, int k,
		FrequencyStyle style)
{
	ranges = std::move(collection.group(k, style));
}

void DataGroupTable::insert(double frequency)
{
	auto&& nextRange = ranges.back()->stack(frequency);
	ranges.push_back(std::move(nextRange));
}

void DataGroupTable::forEach(const std::function<void(const IDataGroup&)>& f) const
{
	for (const auto& range : ranges)
	{
		f(*range);
	}
}
