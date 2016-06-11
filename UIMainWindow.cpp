#include "UIMainWindow.h"
#include <memory> // std::unique_ptr
#include <typeinfo> // std::typeid

#include <QCalendarWidget>
#include "TaskItem.h"   // QMaps for strings connected with task status and priority

#include "TreeModel.h"
#include "TreeItemBase.h"

#include <QStatusBar>
#include <QItemSelection>
#include <QMenu>
#include <QAction>

#include "ProjectItem.h"
#include "TaskItem.h"
#include "TimeInterval.h"

#include "QSignalMapper"


UIMainWindow::UIMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ItemInfoLayoutManager(*this)
    , m_SQLiteDBManager("./testdb.sqlite")
{
    this->setupUI();
    this->connectUISignals();
}

UIMainWindow::~UIMainWindow()
{
    if (nullptr != m_pCentralWidget )
    {
        delete m_pCentralWidget;
    }
}

void UIMainWindow::setupUI()
{
    // Create widget which will store all custom application layout.
    // This widget must be set as central widget in QMainWindow class.
    m_pCentralWidget = new QWidget();
    // Create main layout
    m_pMainLayout = new QVBoxLayout();
    // Add custom layout to widget holder
    m_pCentralWidget->setLayout(m_pMainLayout);
    // Set custom layout to central space in QMainWindow class
    this->setCentralWidget(m_pCentralWidget);

    this->setGeometry(300,300, 600,400);

    // #######################################
    // Create and prepare layout to store:
    // tree widget on the left and layouts (on the right) to present information about selected item
    m_pDataLayout = new QHBoxLayout();
    // add this sub-layout to the main layout
    m_pMainLayout->addLayout(m_pDataLayout);

    m_pDataSplitter = new QSplitter();
    m_pDataLayout->addWidget(m_pDataSplitter);

    m_pTreeView = new QTreeView();
    m_pTreeView->setContextMenuPolicy(Qt::CustomContextMenu); //emit signal when right click

    TreeModel * ownModel = new TreeModel(m_SQLiteDBManager);
    m_pTreeView->setModel(ownModel);
    // appned tree view and info layout to the splitter
    m_pDataSplitter->addWidget(m_pTreeView);

    // append item info view widget to right space of splitter
    m_pDataSplitter->addWidget(m_ItemInfoLayoutManager.getItemInfoViewWidgets());
    // Set item info layout to default
    m_ItemInfoLayoutManager.setCurrentLayout(ItemInfoLayoutManager::InfoLayoutType::Empty);

    // #######################################

}



void UIMainWindow::connectUISignals()
{
    connect(m_pTreeView->selectionModel(), &QItemSelectionModel::selectionChanged
                   , &m_ItemInfoLayoutManager, &ItemInfoLayoutManager::treeItemSelectedAction);

    // connect TreeView item for context menu signal
    connect(m_pTreeView, &QTreeView::customContextMenuRequested
                   , this, &UIMainWindow::showTreeViewContextMenu);

    // connect selection of create new item option on tree view context menu
    connect(this, &UIMainWindow::treeContextAddItemTrigerred
                   , &m_ItemInfoLayoutManager, &ItemInfoLayoutManager::treeContextCreateNewItemAction);

    // connect selection of delete item option on tree view context menu
    connect(this, &UIMainWindow::treeContextDelItemTrigerred
                   , &m_ItemInfoLayoutManager, &ItemInfoLayoutManager::treeContextDeleteItemAction);
}


void UIMainWindow::showTreeViewContextMenu(const QPoint & point)
{
    QModelIndex idx = m_pTreeView->indexAt(point);
    if (false == idx.isValid())
    {
        return;
    }

    auto * selItem = TreeModel::GetInternalPointer(idx);
    QMenu menu;
    QAction * addProj = new QAction("Add new project", &menu);
    switch (selItem->getType())
    {
    case TreeItemType::Project:
        menu.addAction(addProj);
        menu.addAction("Add new time interval");
        menu.addAction("Delete");
        break;
    case TreeItemType::TimeInterval:
        menu.addAction("Add new task");
        menu.addAction("Delete");
        break;
    case TreeItemType::Task:
        menu.addAction("Delete");
        break;
    default:
        return;
        break;
    };

    QAction * ret = menu.exec(m_pTreeView->mapToGlobal(point));

    if (nullptr != ret)
    {
        QString txt = ret->text();
        if (true == txt.contains("add", Qt::CaseInsensitive))
        {
            // Special tratement for adding new project -> need to pass index for root item
            if (true == txt.contains("project", Qt::CaseInsensitive))
            {
                // get root index
                QModelIndex p = idx;
                while (true == p.parent().isValid())
                {
                    p = p.parent();
                }
                p = p.parent(); // get eventually root item
                // emit signal with root index to indicate to create the project item
                emit treeContextAddItemTrigerred(p);
            }
            else
            {
                emit treeContextAddItemTrigerred(idx);
            }
        }
        else if (true == txt.contains("delete", Qt::CaseInsensitive))
        {
            emit treeContextDelItemTrigerred(idx);
        }
    }
}



