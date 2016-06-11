#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include "ItemInfoLayoutManager.h"

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTreeView>
#include <QSplitter>


#include "SQLiteAccess.h"

using namespace sql_data_storage;

class QItemSelection;

class UIMainWindow : public QMainWindow
{
    Q_OBJECT

    friend class ItemInfoLayoutManager;

public:
    explicit UIMainWindow(QWidget *parent = nullptr);

    ~UIMainWindow();

public:


signals:
    void treeContextAddItemTrigerred(const QModelIndex & index);
    void treeContextDelItemTrigerred(const QModelIndex & index);


private slots:
    void showTreeViewContextMenu(const QPoint & point);

private:
    void setupUI() ;
    void connectUISignals();


private:
    /// This widget represents custom application layout it must be created and it is
    /// using to set custom layout in QMainWindow class.
    QWidget     * m_pCentralWidget {nullptr};
    /// Main application layout
    QVBoxLayout * m_pMainLayout {nullptr};


    /// #######################################################################
    /// For listing projects, timeintervals and tasks. In second 'column'
    /// info will be showing about selected item (project, time interval, tasks)
    QHBoxLayout * m_pDataLayout {nullptr};

    /// Adding ability to resize the width of treeview and item information
    QSplitter   * m_pDataSplitter {nullptr};

    /// Tree view for listing projects, time intervals and tasks
    QTreeView * m_pTreeView {nullptr};


    /// #######################################################################


    QLabel      * m_pLableOne {nullptr};


    ItemInfoLayoutManager m_ItemInfoLayoutManager;


    //#########################################################################
    // non UI objects
    SQLiteAccess m_SQLiteDBManager;

};

#endif // UIMAINWINDOW_H
