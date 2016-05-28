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
    SQLiteAccess(const QString & path);
    virtual ~SQLiteAccess();


    // Implement DataStorageAccessInterface interface
public:
    void open() override;
    void close() override;
    ProjectsContainerType getAllProjects() override;
    task_type getTaskItem(const timeint_type &timeInterval) override;
    timeint_type getTimeInterval(const project_type &proj) override;
    void upadteProject(const project_type &proj) override;
    void updateTaskItem(const task_type &task) override;
    void updateTimeInterval(const timeint_type &timeInterval) override;
    void addProject(const project_type &proj) override;
    void addTaskItem(const task_type &task) override;
    void addTimeInterval(const timeint_type &timeInterval) override;
    void removeProjectItem(const project_type &proj) override;
    void removeTaskItem(const task_type &task) override;
    void removeTimeInterval(const timeint_type &timeInterval) override;


protected:
    void createTables();
    void checkQueryError(const QSqlQuery & query) const;

protected:

    QString      m_SQLitePath;  /// Path to the SQLite database file
    QSqlDatabase m_DB;          /// SQLite Database object

};


} // end of namespace
#endif // SQLITEACCESS_H
