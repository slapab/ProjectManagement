#ifndef ITEMSHIERARCHYBUILDER_H
#define ITEMSHIERARCHYBUILDER_H

#include "DataStorageAccessInterface.h"

class ItemsHierarchyBuilder
{
public:
    using ProjectsContainerType = DataStorageAccessInterface::ProjectsContainerType;
    ItemsHierarchyBuilder(DataStorageAccessInterface & dataAccessManager);

    ProjectsContainerType buildWholeHierarchy();

protected:
    DataStorageAccessInterface & m_DataAccessManager;
};

#endif // ITEMSHIERARCHYBUILDER_H
