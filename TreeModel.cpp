#include "TreeModel.h"
#include "TreeItemRoot.h"
#include "ItemsHierarchyBuilder.h"

TreeModel::TreeModel(DataStorageAccessInterface & dataAccessObject)
    : m_DataAccessObject(dataAccessObject)
{
    QList<QVariant> rootData;
    rootData << "Projects" << "Time intervals" << "Tasks";

    // create tree model based on data which can be retrieved from m_DataAccessObject
    m_rootItem = std::make_unique<TreeItemRoot>(std::move(rootData), m_DataAccessObject);
}


TreeItemInterface * TreeModel::GetInternalPointer(const QModelIndex &index)
{
    if (false == index.isValid())
    {
        return nullptr;
    }

    return static_cast<TreeItemInterface *>(index.internalPointer());
}

QVariant TreeModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    TreeItemInterface * item = static_cast<TreeItemInterface*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return m_rootItem->data(section);
    }

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex & parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItemInterface * parentTreeItem = nullptr;

    if (!parent.isValid())
    {
        parentTreeItem = m_rootItem.get(); // return the root item
    }
    else
    {
        parentTreeItem = static_cast<TreeItemInterface*>(parent.internalPointer());
    }

    TreeItemInterface * childTreeItem = parentTreeItem->child(row);
    if (nullptr != childTreeItem)
    {
        return createIndex(row, column, childTreeItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItemInterface * childTreeItem = static_cast<TreeItemInterface*>(index.internalPointer());
    if (childTreeItem == nullptr)
    {
        return QModelIndex();
    }

    TreeItemInterface * parentTreeItem = childTreeItem->parent();

    if (nullptr == parentTreeItem)
    {
        return QModelIndex();
    }

    if (m_rootItem.get() /*compare addresses*/ == parentTreeItem)
    {
        return QModelIndex();
    }

    return createIndex(parentTreeItem->childNumber(childTreeItem), 0, parentTreeItem);
}


int TreeModel::rowCount(const QModelIndex & parent) const
{
    TreeItemInterface * parentTreeItem = nullptr;

    if (0 < parent.column())
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentTreeItem = m_rootItem.get();
    }
    else
    {
        parentTreeItem = static_cast<TreeItemInterface*>(parent.internalPointer());
    }

    return parentTreeItem->childCount();
}

int TreeModel::columnCount(const QModelIndex & parent) const
{
    if (true == parent.isValid())
    {
        return static_cast<TreeItemInterface*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}

// this method just use the beginInsertRows() and endInsertRows(), because
// own implementation assume that tree child is created with custom data and
// can not be set as QVariant
bool TreeModel::insertRows(int position, int rows, const QModelIndex & parent)
{
    beginInsertRows(parent, position, position + rows - 1);
//    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return true;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex & parent)
{
    TreeItemInterface * parentItem = nullptr;

    if (false == parent.isValid())
    {
    // Handle root item
        parentItem = m_rootItem.get();
    }
    else
    // Normal item
    {
       parentItem = GetInternalPointer(parent);
    }

    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

bool TreeModel::insertProject(project_ptr_type projItem)
{
    m_rootItem->createChild(std::move(projItem));
}



