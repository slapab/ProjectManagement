#include "TreeItemBase.h"
#include <algorithm>
#include <exception>

TreeItemBase::TreeItemBase(TreeItemInterface * parent)
    : m_pParent(parent)
{}


TreeItemInterface * TreeItemBase::child(int number)
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

int TreeItemBase::childCount() const
{
    return m_Childs.size();
}

int TreeItemBase::columnCount() const
{
    return 1; // First represent item name, second is the QVariant with
              // UniquePtrForQVariant class that store refernece to the unique_ptr of TreeItem_x_
}


TreeItemInterface * TreeItemBase::parent()
{
    return m_pParent;
}

int TreeItemBase::childNumber(const std::unique_ptr<TreeItemInterface> & child) const
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
int TreeItemBase::childNumber(const TreeItemInterface * const child) const
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


