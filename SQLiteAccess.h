#ifndef SQLITEACCESS_H
#define SQLITEACCESS_H

#include <QSqlDatabase>
#include <QString>
#include <exception>

#include "DataStorageAccessInterface.h"

namespace sql_data_storage
{

namespace exceptions
{
    class SQLiteConnectionException : public std::exception
    {
    public:
        virtual ~SQLiteConnectionException() {}
        explicit SQLiteConnectionException(const char * info);
        explicit SQLiteConnectionException(const QString & info);
        explicit SQLiteConnectionException(QString && info);
        const char * what() const throw() override;

    protected:
        QString m_info;
    };


    /**
     *  Query exception
    */
    class SQLiteQueryException : public std::exception
    {
    public:
        virtual ~SQLiteQueryException() {}
        explicit SQLiteQueryException(const char * info);
        explicit SQLiteQueryException(const QString & info);
        explicit SQLiteQueryException(QString && info);
        const char * what() const throw() override;

    protected:
        QString m_info;
    };
}


class SQLiteAccess : public DataStorageAccessInterface
{
public:
    virtual ~SQLiteAccess();

    SQLiteAccess(const QString & path);

    SQLiteAccess(const SQLiteAccess &) = default;
    SQLiteAccess & operator=(const SQLiteAccess &) = default;

    SQLiteAccess(SQLiteAccess &&) = default;
    SQLiteAccess & operator=(SQLiteAccess &&) = default;


    // Implement DataStorageAccessInterface interface
public:
    void open() override;
    void close() override;
    ProjectsContainerType getAllProjects() override;
    TasksContainerType getTasks(const TimeIntervalInterface &timeInterval) override;
    TimeIntContainerType getTimeIntervals(const ProjectItemInterface &proj) override;

    void updateProject(const ProjectItemInterface & proj) override;
    void updateTaskItem(const TaskItemInterface & task) override;
    void updateTimeInterval(const TimeIntervalInterface & timeInterval) override;

    project_ptr_type addProject(QString name, QString descr, QDateTime beginDate, QDateTime endDate) override;
    task_ptr_type addTaskItem(int intervalID, TaskPriority priority,
                     TaskState state, QString name,
                     QString descr, QDateTime beginDate, QDateTime endDate) override;
    timeint_ptr_type addTimeInterval(int projectID, QString name, QString description, QDateTime beginDate, QDateTime endDate) override;

    void removeProjectItem(const project_ptr_type & proj) override;
    void removeTaskItem(const task_ptr_type & task) override;
    void removeTimeInterval(const timeint_ptr_type & timeInterval) override;


protected:
    void createTables();
    void checkQueryError(const QSqlQuery & query) const;
    int  addingHelper_readID(QSqlQuery & query);

protected:

    QString      m_SQLitePath;  /// Path to the SQLite database file
    QSqlDatabase m_DB;          /// SQLite Database object


};


} // end of namespace
#endif // SQLITEACCESS_H
