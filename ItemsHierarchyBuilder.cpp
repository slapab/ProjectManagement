#include "ItemsHierarchyBuilder.h"

ItemsHierarchyBuilder::ItemsHierarchyBuilder(DataStorageAccessInterface & dataAccessManager)
    : m_DataAccessManager(dataAccessManager)
{}

ItemsHierarchyBuilder::ProjectsContainerType ItemsHierarchyBuilder::buildWholeHierarchy()
{
    m_DataAccessManager.open();

    auto allProjects = m_DataAccessManager.getAllProjects();

    for (const auto & projItem : allProjects)
    {
        // get time intervals assigned to each project
        auto allProjectTimes = m_DataAccessManager.getTimeIntervals(projItem);

        for (const auto & timeItem : allProjectTimes)
        {
            // get all tasks assigned to each time interval
            auto allTimeTasks = m_DataAccessManager.getTasks(timeItem);

            // move tasks container to time interval
            timeItem->setTasksContainer(std::move(allTimeTasks));
        }

        // move time intervals container to the prject
        projItem->setTimeIntervalsContainer(std::move(allProjectTimes));
    }

    // finished, close database and return container with filled dat
    m_DataAccessManager.close();

    return std::move(allProjects);
}


