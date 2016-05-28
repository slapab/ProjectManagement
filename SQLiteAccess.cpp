
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include "SQLiteAccess.h"

using namespace sql_data_storage;


// Define here the exceptions classes
namespace sql_data_storage
{
namespace exceptions
{

SQLiteConnectionException::SQLiteConnectionException(const QString & info)
    : m_info(info)
{}

SQLiteConnectionException::SQLiteConnectionException(const char * info)
    : m_info(info)
{}
SQLiteConnectionException::SQLiteConnectionException(QString && info)
    : m_info(std::move(info))
{}

const char * SQLiteConnectionException::what() const throw()
{
    return m_info.toStdString().c_str();
}


// Implement the SQLiteQueryException

SQLiteQueryException::SQLiteQueryException(const QString & info)
    : m_info(info)
{}

SQLiteQueryException::SQLiteQueryException(const char * info)
    : m_info(info)
{}

SQLiteQueryException::SQLiteQueryException(QString && info)
    : m_info(std::move(info))
{}

const char * SQLiteQueryException::what() const throw()
{
    return m_info.toStdString().c_str();
}

} //namespace
}







SQLiteAccess::SQLiteAccess(const QString & path)
    : m_SQLitePath(path)
    , m_DB(QSqlDatabase::addDatabase("QSQLITE"))
{
    m_DB.setDatabaseName(path);
    m_DB.close();
}

SQLiteAccess::~SQLiteAccess()
{
    this->close();
}

void SQLiteAccess::open()
{
    m_DB.setConnectOptions("foreign_keys = ON");

    if (false == m_DB.open())
    {
        QString errText = m_DB.lastError().text();
        throw exceptions::SQLiteConnectionException(errText);
    }
    else
    {
        createTables();
    }
}

void SQLiteAccess::close()
{
    if (true == m_DB.isOpen())
    {
        m_DB.close();
    }
}

DataStorageAccessInterface::ProjectsContainerType SQLiteAccess::getAllProjects()
{

    // todo check if connection is open?

    // Create empty container for projects data
    ProjectsContainerType projects;

    QSqlQuery query(m_DB);

    query.exec("SELECT project_id, name, description, create_date, end_date FROM projects_table");

    checkQueryError(query);


    auto qRecord = query.record();
    // read data and create objects
    while(true == query.next())
    {
        // Crewate Project object with data read from database
        auto proj = std::make_unique<ProjectItem>
                (
                  query.value(0).toInt()        //get id
                , query.value(1).toString()     //get name
                , query.value(2).toString()     //get descr
                , query.value(3).toDate()       //get create date
                , query.value(4).toDate()       //get end date
                );

        // move project object to the container
        projects.push_back(std::move(proj));
    }

    return projects;
}

DataStorageAccessInterface::task_type SQLiteAccess::getTaskItem(const DataStorageAccessInterface::timeint_type &timeInterval)
{

}

DataStorageAccessInterface::timeint_type SQLiteAccess::getTimeInterval(const DataStorageAccessInterface::project_type &proj)
{

}

void SQLiteAccess::upadteProject(const DataStorageAccessInterface::project_type &proj)
{

}

void SQLiteAccess::updateTaskItem(const DataStorageAccessInterface::task_type &task)
{

}

void SQLiteAccess::updateTimeInterval(const DataStorageAccessInterface::timeint_type &timeInterval)
{

}

void SQLiteAccess::addProject(const DataStorageAccessInterface::project_type &proj)
{

}

void SQLiteAccess::addTaskItem(const DataStorageAccessInterface::task_type &task)
{

}

void SQLiteAccess::addTimeInterval(const DataStorageAccessInterface::timeint_type &timeInterval)
{

}

void SQLiteAccess::removeProjectItem(const DataStorageAccessInterface::project_type &proj)
{

}

void SQLiteAccess::removeTaskItem(const DataStorageAccessInterface::task_type &task)
{

}

void SQLiteAccess::removeTimeInterval(const DataStorageAccessInterface::timeint_type &timeInterval)
{

}


void SQLiteAccess::createTables()
{
    QSqlQuery query(m_DB);


    query.exec(
        "CREATE TABLE IF NOT EXISTS `projects_table` (\
            `project_id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
            `name` TEXT NOT NULL,\
            `description` TEXT,\
            `create_date` TEXT NOT NULL,\
            `end_date` TEXT\
        )");

    // validate the query and throw exception if any problem arise
    checkQueryError(query);



    query.exec(
        "CREATE TABLE IF NOT EXISTS `intervals_table` (\
            `interval_id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
            `project_id` INTEGER NOT NULL REFERENCES `projects_table`(`project_id`) ON UPDATE CASCADE ON DELETE CASCADE,\
            `name` TEXT NOT NULL,\
            `description` TEXT,\
            `begin_date` TEXT NOT NULL,\
            `end_date` TEXT NOT NULL\
        )");

    checkQueryError(query);



    query.exec(
        "CREATE TABLE IF NOT EXISTS `tasks_table` (\
            `task_id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
            `inverval_id` INTEGER NOT NULL REFERENCES `intervals_table`(`interval_id`) ON UPDATE CASCADE ON DELETE CASCADE,\
            `name` TEXT NOT NULL,\
            `description` TEXT,\
            `begin_date` TEXT,\
            `end_date` TEXT,\
            `priority` INTEGER NOT NULL,\
            `state` INTEGER NOT NULL\
        )");

    checkQueryError(query);
}


void SQLiteAccess::checkQueryError(const QSqlQuery & query) const
{
    auto err = query.lastError();

    if (true == err.isValid())
    {
        exceptions::SQLiteQueryException e(err.text());
        throw e;
    }
}

