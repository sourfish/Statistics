#include "ConsolePresenter.hpp"
#include "DataCollection.hpp"
#include "DataGroup.hpp"
#include "DataGroupTable.hpp"

int main()
{
	DataGroup startingGroup(1.0, 10.0, 0);
	startingGroup.setFrequency(4.0);
	startingGroup.setCumulativeFrequency(startingGroup.getFrequency());

	DataGroupTable manualDataTable(startingGroup);
	manualDataTable.insert(1);
	manualDataTable.insert(2);
	manualDataTable.insert(4);
	manualDataTable.insert(3);

	DataCollection collection({ 2.0, 4.0, 7.0, 1.6, 13.2, 15.8 });
	DataGroupTable autoDataTable(collection, 3, FrequencyStyle::RAW);

	ConsolePresenter console;
	console.present(manualDataTable);
	console.present(autoDataTable);

	return 0;
}
