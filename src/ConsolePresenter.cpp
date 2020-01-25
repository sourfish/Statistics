// ConsolePresenter.cpp

#include "ConsolePresenter.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "DataGroupTable.hpp"
#include "IDataCollection.hpp"
#include "IDataGroup.hpp"

ConsolePresenter::ConsolePresenter()
{
	tableWidth = 15;
}

ConsolePresenter::ConsolePresenter(int tableWidth)
{
	assert(tableWidth > 0);
	this->tableWidth = tableWidth;
}

void ConsolePresenter::setTableWidth(int tableWidth)
{
	assert(tableWidth > 0);
	this->tableWidth = tableWidth;
}

int ConsolePresenter::getTableWidth() const
{
	return tableWidth;
}

void ConsolePresenter::present(const DataGroupTable& data) const
{
	std::cout << std::left
			  << std::setw(tableWidth) << "Limits"
			  << std::setw(tableWidth) << "Bounds"
			  << std::setw(tableWidth) << "Midpoint"
			  << std::setw(tableWidth) << "f"
			  << std::setw(tableWidth) << "cf"
			  << std::endl;

	data.forEach([this](const IDataGroup& range)
	{
		present(range);
	});

	std::cout << std::endl;
}

void ConsolePresenter::present(const IDataGroup& range) const
{
	std::stringstream bounds, smoothBounds;
	bounds << range.getLowerBound() << " - " << range.getUpperBound();
	smoothBounds << range.getSmoothLowerBound() << " - " << range.getSmoothUpperBound();

	std::cout << std::left
			  << std::setw(tableWidth) << bounds.str()
			  << std::setw(tableWidth) << smoothBounds.str()
			  << std::setw(tableWidth) << range.getMidpoint()
			  << std::setw(tableWidth) << range.getFrequency()
			  << std::setw(tableWidth) << range.getCumulativeFrequency()
			  << std::endl;
}

void ConsolePresenter::present(const IDataCollection& collection) const
{
	collection.forEach([](double value)
	{
		std::cout << value << " ";
	});

	std::cout << std::endl;
}
