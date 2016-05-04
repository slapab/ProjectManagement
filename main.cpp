#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDate>
#include "ProjectItem.h"
#include "ItemsFactory.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    ItemsFactory factory;
    QString name = "MojaNazwa2";
    auto pProjItem = factory.GetProject(name, "Opis", QDate::currentDate());
//    pProjItem->setName("ZmieniamNazwe");

    qDebug() << pProjItem->getName() << pProjItem->getDescription() << pProjItem->getDate() ;

    return 0;
}
