#include "TreeItemRoot.h"

TreeItemRoot::TreeItemRoot(QList<QVariant> && data, DataStorageAccessInterface & dataAccessObject)
    : m_pParent {nullptr} // root never has parent
    , m_DataAccessObject {dataAccessObject}
    , m_RootData {std::move(data)}
{
    auto projects = m_DataAccessObject.getAllProjects();
    
    for (size_t i = 0; i < projects.size(); ++i)
    {
        try
        {
            m_Childs.push_back(std::make_unique<TreeItem>(std::move(projects[i])
                                                                                                   , this
                                                                                                   , m_DataAccessObject));
        }
        catch (...)
        {}
    }
}

QVariant TreeItemRoot::data(int column) const
{
    return m_RootData.value(column);
}

ItemInterface & TreeItemRoot::getUnderlaidData()
{
    // this is not allowed so throw exception
    throw std::out_of_range("Root tree node has not underlaid data!");
}


