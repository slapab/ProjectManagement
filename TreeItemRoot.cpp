#include "TreeItemRoot.h"

#include "TreeItemProject.h"

TreeItemRoot::TreeItemRoot(const ProjectsContainerType & projects, QList<QVariant> && data)
    : TreeItemBase(nullptr) // Root never has parent
    , m_ProjectsContainer(projects)
    , m_RootData(std::move(data))
{
    // Create tree projects child with data stored in m_ProjectsContainer
    for (const auto & projItem : m_ProjectsContainer)
    {
        m_Childs.push_back(std::make_unique<TreeItemProject>(
                                  projItem  // project item is source of data for this tree child
                                , this      // this tree root is the parent for each project child
                           ));
    }

    // Create the label strings
}

QVariant TreeItemRoot::data(int column) const
{
    return m_RootData.value(column);
}

ItemInterface & TreeItemRoot::getUnderlaidData()
{
    // this is not allowed so throw exception
    throw std::out_of_range("Root node has not underlaid data");
}


