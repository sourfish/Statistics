// DataCollection.hpp

#ifndef DATACOLLECTION_HPP_
#define DATACOLLECTION_HPP_

#include "IDataCollection.hpp"

class DataCollection : public IDataCollection
{
public:
	DataCollection();
	DataCollection(const std::vector<double>& values);

	void insert(double value) override;

	void forEach(const std::function<void(double)>& f) const override;
	double getMin() const override;
	double getMax() const override;
	double getRange() const override;
	double getMedian() const override;
	double getMean() const override;
	double getFrequency(double lowerBound, double upperBound) const override;
	int getPrecision() const override;
	int getSize() const override;

	std::vector<std::unique_ptr<IDataGroup>> group(int k, FrequencyStyle style) const override;

private:
	static int getPrecision(double value);
	static double roundUp(double value, int precision);

	std::vector<double> values;
	double sum;
};

#endif /* DATACOLLECTION_HPP_ */
