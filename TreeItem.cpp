#include "TreeItem.h"
#include <algorithm>
#include <exception>


TreeItem::TreeItem(project_ptr_type projItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject)
    : m_TreeItemType {TreeItemType::Project}
    , m_pParent {parent}
    , m_itemData {std::move(projItem)}
    , m_DataAccessObject {dataAccessObject}
{
    if (nullptr == m_itemData.get())
    {
        throw std::invalid_argument("Empty item");
    }
    
    
    auto timeIntervals = m_DataAccessObject.getTimeIntervals(static_cast<ProjectItemInterface&>(*m_itemData.get()));
    
    for (size_t i = 0; i < timeIntervals.size(); ++i)
    {
        try
        {
            m_Childs.push_back(std::make_unique<TreeItem>(std::move(timeIntervals[i])
                                                        , this
                                                        , m_DataAccessObject));
        }
        catch(...)
        {}
    }
}


TreeItem::TreeItem(timeint_ptr_type timeintItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject)
    : m_TreeItemType {TreeItemType::TimeInterval}
    , m_pParent {parent}
    , m_itemData {std::move(timeintItem)}
    , m_DataAccessObject {dataAccessObject}
{
    if (nullptr == m_itemData.get())
    {
        throw std::invalid_argument("Empty item");
    }
    
    
    auto tasks = m_DataAccessObject.getTasks(static_cast<TimeIntervalInterface&>(*m_itemData.get()));
    
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        try
        {
            m_Childs.push_back(std::make_unique<TreeItem>(std::move(tasks[i])
                                                        , this
                                                        , m_DataAccessObject));
        }
        catch(...)
        {}
    }
}

TreeItem::TreeItem(task_ptr_type taskItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject)
    : m_TreeItemType {TreeItemType::Task}
    , m_pParent {parent}
    , m_itemData {std::move(taskItem)}
    , m_DataAccessObject {dataAccessObject}
{
    // task item has not any children
    
    if (nullptr == m_itemData.get())
    {
        throw std::invalid_argument("Empty item");
    }
}

// Constructor for root item
TreeItem::TreeItem(TreeItemInterface *parent, DataStorageAccessInterface &dataAccessObject)
    : m_TreeItemType {TreeItemType::Root}
    , m_pParent(parent)
    , m_DataAccessObject(dataAccessObject)
{}


TreeItemInterface * TreeItem::child(int number)
{
    try
    {
        return m_Childs.at(number).get();
    }
    catch (...)
    {
        return nullptr;
    }
}

int TreeItem::childCount() const
{
    return m_Childs.size();
}

int TreeItem::columnCount() const
{
    return 1; // represent item name
}


TreeItemInterface * TreeItem::parent()
{
    return m_pParent;
}

TreeItemType TreeItem::getType() const
{
    return m_TreeItemType;
}


int TreeItem::childNumber(const TreeItemInterface * const child) const
{
    if (nullptr == child)
    {
        return 0;
    }

    // make predicator to compare addresses
    auto pred = [&child](const auto & item /*unique_ptr*/) -> bool {
        return (item.get() == child); // compare addresses
    };

    auto iter = std::find_if(m_Childs.begin(), m_Childs.end(), pred);

    if (m_Childs.end() != iter)
    {
        return std::distance(m_Childs.begin(), iter);
    }

    return 0;
}


QVariant TreeItem::data(int column) const
{
    return QVariant(m_itemData->getName());
}

ItemInterface & TreeItem::getUnderlaidData()
{
    if (nullptr == m_itemData.get())
    {
        // this situation should never happen, if pointer to data is empty, then this tree item should be deleted
        throw std::invalid_argument("This tree node has empty underlaid data! This node need to be deleted!");
    }
    
    return *m_itemData.get();
}
