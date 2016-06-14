#include "TreeItemRoot.h"

TreeItemRoot::TreeItemRoot(QList<QVariant> && data, DataStorageAccessInterface & dataAccessObject)
    : TreeItem {nullptr, dataAccessObject} // root never has parent
    , m_RootData {std::move(data)}
{
    m_DataAccessObject.open();

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

    m_DataAccessObject.close();
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


