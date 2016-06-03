
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include "SQLiteAccess.h"
#include "ProjectItem.h"
#include "TaskItem.h"
#include "TimeInterval.h"

using namespace sql_data_storage;

using project_ptr_type = DataStorageAccessInterface::project_ptr_type;
using task_ptr_type = DataStorageAccessInterface::task_ptr_type;
using timeint_ptr_type = DataStorageAccessInterface::timeint_ptr_type;
using ProjectsContainerType = DataStorageAccessInterface::ProjectsContainerType;
using TasksContainerType = DataStorageAccessInterface::TasksContainerType;
using TimeIntContainerType = DataStorageAccessInterface::TimeIntContainerType;


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

ProjectsContainerType SQLiteAccess::getAllProjects()
{

    if (false == m_DB.isOpen())
    {
        throw exceptions::SQLiteConnectionException("Database connection is closed");
    }

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
                , QDateTime::fromTime_t(query.value(3).toUInt()) //get create date
                , QDateTime::fromTime_t(query.value(4).toUInt()) //get end date
                );

        // move project object to the container
        projects.push_back(std::move(proj));
    }

    return projects;
}

TasksContainerType SQLiteAccess::getTasks(const timeint_ptr_type &timeInterval)
{

    QSqlQuery query(m_DB);
    query.prepare(
        "SELECT "
        " task_id, name, description, begin_date, end_date, priority, state "
        " FROM "
        " tasks_table "
        " WHERE "
        " interval_id = (:id)"
        );

    // get only tasks that are assigned to the given time interval
    query.bindValue(":id", timeInterval->getID());

    if (false == query.exec())
    {
        // throw exception if failed
        checkQueryError(query);
    }

    // Get all tasks that are assigned to the given timeinterval
    auto qRecord = query.record();

    TasksContainerType tasks;
    while(true == query.next())
    {
        // Create task object with data read from database
        auto obj = std::make_unique<TaskItem>
                (
                  query.value(0).toInt()        //get id
                , timeInterval->getID()         //TimeIntervalID
                , static_cast<TaskPriority>(query.value(5).toInt()) //get priority
                , static_cast<TaskState>(query.value(6).toInt())    //get state
                , query.value(1).toString()     //get name
                , query.value(2).toString()     //get description
                , QDateTime::fromTime_t(query.value(3).toUInt()) //get begin date
                , QDateTime::fromTime_t(query.value(4).toUInt()) //get end date
                );

        // move object to the container
        tasks.push_back(std::move(obj));
    }

    // move container
    return tasks;
}

TimeIntContainerType SQLiteAccess::getTimeIntervals(const project_ptr_type &proj)
{

    QSqlQuery query(m_DB);
    query.prepare(
        "SELECT "
        " interval_id, name, description, begin_date, end_date "
        " FROM "
        " intervals_table "
        " WHERE "
        " project_id = (:id)"
        );

    // bind the project name
    query.bindValue(":id", proj->getID());

    if (false == query.exec())
    {
        // throw exception if failed
        checkQueryError(query);
    }

    // Get all time intervals assigned to the given project
    auto qRecord = query.record();

    TimeIntContainerType intervals;
    while(true == query.next())
    {
        // Create time interval object with data read from database
        auto obj = std::make_unique<TimeInterval>
                (
                  query.value(0).toInt()        //get id
                , proj->getID()                 //save project ID
                , query.value(1).toString()     //get priority
                , query.value(2).toString()     //get state
                , QDateTime::fromTime_t(query.value(3).toUInt()) //get begin date
                , QDateTime::fromTime_t(query.value(4).toUInt()) //get end date
                );

        // move object to the container
        intervals.push_back(std::move(obj));
    }

    // move container
    return intervals;
}

void SQLiteAccess::upadteProject(const project_ptr_type &proj)
{
    QSqlQuery query(m_DB);

    query.prepare(
                "UPDATE projects_table SET "
                " name=':NAME' "
                ", description=':DESCR' "
                ", create_date=':CREATEDATE' "
                ", end_date=':ENDDATE' "
                " WHERE "
                " project_id = ':PROJID'"
                );

    query.bindValue(":PROJID", proj->getID());
    query.bindValue(":NAME", proj->getName());
    query.bindValue(":DESCR", proj->getDescription());

    std::pair<QDateTime, QDateTime> dates = proj->getDates();
    query.bindValue(":CREATEDATE", dates.first.toTime_t());
    query.bindValue(":ENDDATE", dates.second.toTime_t());

    if (false == query.exec())
    {
        checkQueryError(query);
    }
}

void SQLiteAccess::updateTaskItem(const task_ptr_type &task)
{
    QSqlQuery query(m_DB);

    query.prepare(
                "UPDATE tasks_table SET "
                " name=':NAME' "
                ", description=':DESCR' "
                ", begin_date=':BEGDATE' "
                ", end_date=':ENDDATE' "
                ", interval_id=':INTERVALID' "
                ", priorit=':PRIOR' "
                ", state=':STATE' "
                " WHERE task_id = ':TASKID'"
                );

    query.bindValue(":TASKID", task->getID());
    query.bindValue(":NAME", task->getName());
    query.bindValue(":DESCR", task->getDescription());

    auto dates = task->getDates();
    query.bindValue(":BEGDATE", dates.first.toTime_t());
    query.bindValue(":ENDDATE", dates.second.toTime_t());
    query.bindValue(":INTERVALID", task->getIntervalID());
    query.bindValue(":PRIOR", static_cast<int>(task->getPriority()));
    query.bindValue(":STATE", static_cast<int>(task->getState()));

    if (false == query.exec())
    {
        checkQueryError(query);
    }
}

void SQLiteAccess::updateTimeInterval(const timeint_ptr_type &timeInterval)
{
    QSqlQuery query(m_DB);

    query.prepare(
                "UPDATE intervals_table SET "
                " name=':NAME' "
                ", description=':DESCR' "
                ", begin_date=':BEGDATE' "
                ", end_date=':ENDDATE' "
                ", project_id=':PROJID' "
                " WHERE interval_id = ':INTERVALID'"
                );

    query.bindValue(":INTERVALID", timeInterval->getID());
    query.bindValue(":NAME", timeInterval->getName());
    query.bindValue(":DESCR", timeInterval->getDescription());

    auto dates = timeInterval->getDates();
    query.bindValue(":BEGDATE", dates.first.toTime_t());
    query.bindValue(":ENDDATE", dates.second.toTime_t());
    query.bindValue(":PROJID", timeInterval->getProjectID());


    if (false == query.exec())
    {
        checkQueryError(query);
    }
}

project_ptr_type SQLiteAccess::addProject(QString name, QString descr, QDateTime beginDate, QDateTime endDate)
{
    QSqlQuery query(m_DB);

    query.prepare(
                "INSERT INTO projects_table "
                " (name, description, create_date, end_date) "
                " VALUES "
                " (:NAME, :DESCR, :CDATE, :EDATE)"
                );

    query.bindValue(":NAME", name);
    query.bindValue(":DESCR", descr);
    query.bindValue(":CDATE", beginDate.toTime_t());
    query.bindValue(":EDATE", endDate.toTime_t());

    if (false == query.exec())
    {
        checkQueryError(query);
    }

    // get the ID of added project
    query.prepare(
                "SELECT project_id FROM projects_table"
                " WHERE name=(:NAME)"
                );
    query.bindValue(":NAME", name);

    if (false == query.exec())
    {
        checkQueryError(query);
    }

    // get the id
    int id = this->addingHelper_readID(query);

    // create task object and return it
    return std::make_unique<ProjectItem> (
                id, std::move(name), std::move(descr), std::move(beginDate), std::move(endDate)
                );
}

task_ptr_type SQLiteAccess::addTaskItem(
                               int intervalID, TaskPriority priority,
                               TaskState state, QString name,
                               QString descr, QDateTime beginDate, QDateTime endDate)
{
    QSqlQuery query(m_DB);

    query.prepare(
                "INSERT INTO tasks_table "
                " (interval_id, name, description, begin_date, end_date, priority, state) "
                " VALUES "
                " (:INTID, :NAME, :DESCR, :BDATE, :EDATE, :PRIORITY, :STATE)"
                );

    query.bindValue(":INTID", intervalID);
    query.bindValue(":NAME",  name);
    query.bindValue(":DESCR", descr);
    query.bindValue(":BDATE", beginDate.toTime_t());
    query.bindValue(":EDATE", endDate.toTime_t());
    query.bindValue(":PRIORITY", static_cast<int>(priority));
    query.bindValue(":STATE", static_cast<int>(state));

    if (false == query.exec())
    {
        checkQueryError(query);
    }


    // get the ID of added task
    query.prepare(
                "SELECT task_id FROM tasks_table"
                " WHERE name=(:NAME)"
                );
    query.bindValue(":NAME", name);

    if (false == query.exec())
    {
        checkQueryError(query);
    }

    // get the id
    int id = this->addingHelper_readID(query);

    // create project object and return it
    return std::make_unique<TaskItem> (
                id, intervalID, priority, state,
                std::move(name), std::move(descr),
                std::move(beginDate), std::move(endDate)
                );
}

timeint_ptr_type SQLiteAccess::addTimeInterval(int projectID, QString name, QString description, QDateTime beginDate, QDateTime endDate)
{
    QSqlQuery query(m_DB);

    query.prepare(
                "INSERT INTO intervals_table "
                " (project_id, name, description, begin_date, end_date) "
                " VALUES "
                " (:PROJID, :NAME, :DESCR, :BDATE, :EDATE)"
                );

    query.bindValue(":PROJID", projectID);
    query.bindValue(":NAME", name);
    query.bindValue(":DESCR", description);
    query.bindValue(":BDATE", beginDate.toTime_t());
    query.bindValue(":EDATE", endDate.toTime_t());

    if (false == query.exec())
    {
        checkQueryError(query);
    }


    // get the ID of added timeinterval entry
    query.prepare(
                "SELECT interval_id FROM intervals_table"
                " WHERE name=(:NAME)"
                );
    query.bindValue(":NAME", name);

    if (false == query.exec())
    {
        checkQueryError(query);
    }

    // get the id
    int id = this->addingHelper_readID(query);

    // create time interval object and return it
    return std::make_unique<TimeInterval> (
                id, projectID,
                std::move(name), std::move(description),
                std::move(beginDate), std::move(endDate)
                );
}

void SQLiteAccess::removeProjectItem(const project_ptr_type &proj)
{
    QSqlQuery query(m_DB);
    query.prepare(
                "DELETE FROM projects_table "
                " WHERE "
                " project_id = ':PROJID'"
                );

    query.bindValue(":PROJID", proj->getID());

    if (false == query.exec())
    {
        checkQueryError(query);
    }
}

void SQLiteAccess::removeTaskItem(const task_ptr_type &task)
{
    QSqlQuery query(m_DB);

    query.prepare(
                " DELETE FROM tasks_table "
                " WHERE "
                " task_id=':TASKID'"
                );

    query.bindValue(":TASKID", task->getID());

    if (false == query.exec())
    {
        checkQueryError(query);
    }
}

void SQLiteAccess::removeTimeInterval(const timeint_ptr_type &timeInterval)
{
    QSqlQuery query(m_DB);

    query.prepare(
                " DELETE FROM intervals_table "
                " WHERE "
                " interval_id=':INTID'"
                );

    query.bindValue(":INTID", timeInterval->getID());

    if (false == query.exec())
    {
        checkQueryError(query);
    }
}


void SQLiteAccess::createTables()
{
    QSqlQuery query(m_DB);


    query.exec(
        "CREATE TABLE IF NOT EXISTS `projects_table` (\
            `project_id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
            `name` TEXT NOT NULL UNIQUE,\
            `description` TEXT,\
            `create_date` INTEGER NOT NULL,\
            `end_date` INTEGER\
        )");

    // validate the query and throw exception if any problem arise
    checkQueryError(query);


    // intervals_table
    query.exec(
        "CREATE TABLE IF NOT EXISTS `intervals_table` (\
            `interval_id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
            `project_id` INTEGER NOT NULL REFERENCES `projects_table`(`project_id`) ON UPDATE CASCADE ON DELETE CASCADE,\
            `name` TEXT NOT NULL UNIQUE,\
            `description` TEXT,\
            `begin_date` INTEGER NOT NULL,\
            `end_date` INTEGER NOT NULL\
        )");

    checkQueryError(query);


    // tasks_table
    query.exec(
        "CREATE TABLE IF NOT EXISTS `tasks_table` (\
            `task_id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
            `interval_id` INTEGER NOT NULL REFERENCES `intervals_table`(`interval_id`) ON UPDATE CASCADE ON DELETE CASCADE,\
            `name` TEXT NOT NULL UNIQUE,\
            `description` TEXT,\
            `begin_date` INTEGER,\
            `end_date` INTEGER,\
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

int SQLiteAccess::addingHelper_readID(QSqlQuery & query)
{
    // Check if there is ready record to read
    if (false == query.next())
    {
        // nothing good, it should return exactly one row
        // so throw an exception
        exceptions::SQLiteQueryException e{"Problem while adding item into database. Cannot read its key."};
        throw e;
    }

    // Get the record object
    auto rec = query.record();

    // get and return the ID (primary key)
    return rec.value(0).toInt();
}

