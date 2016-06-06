#ifndef TREEITEMINTERFACE_H
#define TREEITEMINTERFACE_H

#include <memory> // for std::unique_ptr
#include <QVariant>


class TreeItemInterface
{
public:
    using ptr_type = std::unique_ptr<TreeItemInterface>;

    virtual ~TreeItemInterface() = default;

    virtual TreeItemInterface * child(int number) = 0;
    virtual int childCount() const = 0;
    virtual int columnCount() const = 0;
    virtual QVariant data(int column) const = 0;
    virtual int childNumber(const std::unique_ptr<TreeItemInterface> & child) const = 0;
    virtual int childNumber(const TreeItemInterface * const child) const = 0;
    virtual TreeItemInterface * parent() = 0;
//    virtual bool insertChildren(int position, int count, int columns) = 0;
//    virtual bool insertColumns(int position, int columns) = 0;
//    virtual bool removeChildren(int position, int count) = 0;
//    virtual bool removeColumns(int position, int columns) = 0;
//    virtual bool setData(int column, const QVariant & value) = 0;


};

#endif // TREEITEMINTERFACE_H
