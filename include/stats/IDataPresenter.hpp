// IDataPresenter.hpp

#ifndef IDATAPRESENTER_HPP_
#define IDATAPRESENTER_HPP_

class IDataGroup;
class IDataCollection;
class DataGroupTable;

class IDataPresenter
{
public:
	virtual ~IDataPresenter() = default;

	virtual void present(const IDataGroup& range) const = 0;
	virtual void present(const IDataCollection& collection) const = 0;
	virtual void present(const DataGroupTable& data) const = 0;
};

#endif /* IDATAPRESENTER_HPP_ */
