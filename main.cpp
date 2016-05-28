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

//    ItemsFactory factory;
//    QString name = "Project 1";
//    auto pProjItem = factory.GetProject(name, "Project 1 descritpion", QDate::currentDate());
////    pProjItem->setName("ZmieniamNazwe");

//    auto pTInterval = factory.GetTimeInterval("Sprint 1", QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(1));


//    qDebug() << "ProjectItem: " << pProjItem->getName() << "\n"
//             << " description: " << pProjItem->getDescription() << "\n"
//             << " creation date: " << pProjItem->getDate() << "\n" ;

//    qDebug() << "TimeInterval: " << pTInterval->getName() << "\n"
//             << " begin date: " << pTInterval->GetDatesRange().first << "\n"
//             << " end date: " << pTInterval->GetDatesRange().second ;

//    auto interval_item = std::make_unique<TimeInterval>(1, 2, "TimeInterval1", "Description one.",
//                                        QDateTime::currentDateTime(),
//                                        QDateTime::currentDateTime().addDays(10));

//    auto interval_item2 = std::make_unique<TimeInterval>(11, 21, "TimeInterval2", "Description one.",
//                                        QDateTime::currentDateTime(),
//                                        QDateTime::currentDateTime().addDays(10));

//    ProjectItem pi(3, "Project1", "", QDate::currentDate(), QDate::currentDate().addMonths(1));

//    qDebug() << interval_item.get();

//    std::vector<std::unique_ptr<TimeInterval>> sab;
//    sab.push_back(std::move(interval_item));


//    pi.addTimeInterval(std::move(interval_item2));
//    pi.setTimeIntervalsContainer(std::move(sab));

//    qDebug() << sab.size();


//    qDebug() << (nullptr == interval_item);

//    qDebug() << pi.getTimeIntervalsContainer().at(0).get();

//    pi.removeTimeInterval(1);

    {
        using namespace sql_data_storage;
        SQLiteAccess dbStorage("/home/scott/Development/QtCreator/MPiMS/testdb.sqlite");
        try
        {
            dbStorage.open();
            auto projs = dbStorage.getAllProjects();
            qDebug() << projs.size();

            for ( const std::unique_ptr<ProjectItem> & it : projs )
            {
                qDebug() << it->getName() << " " << it->getDescription();
            }

        }
        catch( exceptions::SQLiteQueryException & e)
        {
            qDebug() << QString(e.what());
        }

    }

//    qDebug() << QDate::currentDate().toString() << " " << QDate::currentDate().addDays(1).toString();
    return 0;
}
