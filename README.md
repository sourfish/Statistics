# Statistics
This is a small library to help me cheat on my statistics homework and save hours of wasted time building frequency distribution tables.

# Example Usage
```
// Automatic grouping
DataCollection collection({ 2.0, 4.0, 7.0, 1.6, 13.2, 15.8 });
DataGroupTable autoDataTable(collection, 11, FrequencyStyle::RAW);

// Manual grouping
PercentageDataGroup startingGroup(1.0, 10.0, 0, 14);
startingGroup.setFrequency(4.0);
startingGroup.setCumulativeFrequency(4.0);

DataGroupTable manualDataTable(startingGroup);
manualDataTable.insert(1);
manualDataTable.insert(2);
manualDataTable.insert(4);
manualDataTable.insert(3);

// Console output
ConsolePresenter console;
console.present(autoDataTable);
console.present(manualDataTable);
```
