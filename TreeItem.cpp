#include "TreeItem.h"
#include <algorithm>
#include <exception>


TreeItem(project_ptr_type projItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject)
    : m_pParent {parent}
    , m_itemData {std::move(projItem)}
    , m_DataAccessObject {dataAccessObject}
{
    if (nullptr == m_itemData.get())
    {
        throw std::invalid_argument("Empty item");
    }
    
    
    auto timeIntervals = m_DataAccessObject.getTimeIntervals(m_itemData);
    
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


TreeItem(timeint_ptr_type timeintItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject)
    : m_pParent {parent}
    , m_itemData {std::move(projItem)}
    , m_DataAccessObject {dataAccessObject}
{
    if (nullptr == m_itemData.get())
    {
        throw std::invalid_argument("Empty item");
    }
    
    
    auto tasks = m_DataAccessObject.getTasks(m_itemData);
    
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

TreeItem(task_ptr_type taskItem, TreeItemInterface * parent, DataStorageAccessInterface & dataAccessObject)
    : m_pParent {parent}
    , m_itemData {std::move(projItem)}
    , m_DataAccessObject {dataAccessObject}
{
    // task item has not any children
    
    if (nullptr == m_itemData.get())
    {
        throw std::invalid_argument("Empty item");
    }
}



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

int TreeItem::childNumber(const std::unique_ptr<TreeItemInterface> & child) const
{
    if (nullptr == child.get())
    {
        return 0;
    }

    // Find child
    auto iter = std::find(m_Childs.begin(), m_Childs.end(), child);

    if (m_Childs.end() != iter)
    {
        return std::distance(m_Childs.begin(), iter);
    }

    return 0;
}

/*
 * \note    This overload should be deletede if all raw pointers TreeItemInterface *
 *          would be changed to unique_ptr<TreeItemInterface>
 */
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