#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDate>
#include "ProjectItem.h"
#include "ItemsFactory.h"
#include "TimeInterval.h"
#include "SQLiteAccess.h"
#include <memory>
#include <utility>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();


    {
        using namespace sql_data_storage;
        using namespace std;

        SQLiteAccess dbStorage("./testdb.sqlite");
        try
        {
            dbStorage.open();


            { //add new project
                QDateTime now = QDateTime::currentDateTime();
                auto p =  dbStorage.addProject(
                            "New Project", "Project Description", now, now.addDays(3)
                            );

                qDebug() << "New project has been added" << p->getName() << " " << p->getID();
            }


            auto projs = dbStorage.getAllProjects();
            qDebug() << projs.size();

            for ( const auto & it : projs )
            {
                auto dates = it->getDates();
                qDebug() << it->getName() << " " << it->getDescription() << " " << dates.second.toString();

                auto timeIntervals = dbStorage.getTimeIntervals(it);

                for ( const auto & timeItem : timeIntervals )
                {
                    auto dates = timeItem->getDates();
                    qDebug() << "\t" << timeItem->getName() << " " << dates.first.toString();
                }
            }

        }
        catch( exceptions::SQLiteQueryException & e)
        {
            qDebug() << QString(e.what());
        }

    }

    return 0;
}
