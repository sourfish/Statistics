// ConsolePresenter.hpp

#ifndef CONSOLEPRESENTER_HPP_
#define CONSOLEPRESENTER_HPP_

#include "IDataPresenter.hpp"

class ConsolePresenter : public IDataPresenter
{
public:
	ConsolePresenter();
	ConsolePresenter(int tableWidth);

	void setTableWidth(int tableWidth);

	int getTableWidth() const;
	void present(const DataGroupTable& data) const override;
	void present(const IDataGroup& range) const override;
	void present(const IDataCollection& collection) const override;

private:
	int tableWidth;
};

#endif /* CONSOLEPRESENTER_HPP_ */
