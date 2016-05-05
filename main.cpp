#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDate>
#include "ProjectItem.h"
#include "ItemsFactory.h"
#include "TimeInterval.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    ItemsFactory factory;
    QString name = "Project 1";
    auto pProjItem = factory.GetProject(name, "Project 1 descritpion", QDate::currentDate());
//    pProjItem->setName("ZmieniamNazwe");

    auto pTInterval = factory.GetTimeInterval("Sprint 1", QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(1));


    qDebug() << "ProjectItem: " << pProjItem->getName() << "\n"
             << " description: " << pProjItem->getDescription() << "\n"
             << " creation date: " << pProjItem->getDate() << "\n" ;

    qDebug() << "TimeInterval: " << pTInterval->getName() << "\n"
             << " begin date: " << pTInterval->GetDatesRange().first << "\n"
             << " end date: " << pTInterval->GetDatesRange().second ;
    return 0;
}
