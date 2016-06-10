#include "UIMainWindow.h"
#include <memory> // std::unique_ptr
#include <typeinfo> // std::typeid

#include <QCalendarWidget>
#include "TaskItem.h"   // QMaps for strings connected with task status and priority

#include "TreeModel.h"
#include "TreeItemBase.h"

#include <QStatusBar>
#include <QItemSelection>

#include "ProjectItem.h"
#include "TaskItem.h"
#include "TimeInterval.h"


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
   QObject::connect(m_pTreeView->selectionModel(), &QItemSelectionModel::selectionChanged
                   , this, &UIMainWindow::treeItemSelected);

}

UIMainWindow::SelectedItemType UIMainWindow::whichItemSelected(const QModelIndex & index)
{
    int i = 0;
    auto tidx = index;
    while (true == tidx.isValid())
    {
        tidx = tidx.parent();
        ++i;
    }

    SelectedItemType type = SelectedItemType::None;

    switch(i)
    {
    case 1:
        type = SelectedItemType::Project;
        break;
    case 2:
        type = SelectedItemType::TimeInterval;
        break;
    case 3:
        type = SelectedItemType::Task;
        break;
    default:
        break;
    }

    return type;
}

void UIMainWindow::treeItemSelected(const QItemSelection &selected, const QItemSelection &)
{
    auto index = selected.indexes().at(0);

    if (false == index.isValid())
    {
        return;
    }

    // set current layout to item view layout
    m_ItemInfoLayoutManager.setCurrentLayout(ItemInfoLayoutManager::InfoLayoutType::ItemInfo);


    auto * pTreeItemI = TreeModel::GetInternalPointer(index);
    auto type = whichItemSelected(index);

    if (SelectedItemType::Project == type)
    {
        auto & item = dynamic_cast<ProjectItemInterface &>(pTreeItemI->getUnderlaidData());

        m_ItemInfoLayoutManager.fillItemInfoLayout(item, index);
    }
    else if (SelectedItemType::TimeInterval == type)
    {
        auto & item = dynamic_cast<TimeIntervalInterface &>(pTreeItemI->getUnderlaidData());

        m_ItemInfoLayoutManager.fillItemInfoLayout(item, index);
    }
    else if (SelectedItemType::Task == type)
    {
        auto & item = dynamic_cast<TaskItemInterface &>(pTreeItemI->getUnderlaidData());

        m_ItemInfoLayoutManager.fillItemInfoLayout(item, index);
    }
}

// ######################################################
// Implementation for inner class
// ######################################################

UIMainWindow::ItemInfoLayoutManager::~ItemInfoLayoutManager()
{
    // If m_pItemInfoViewWidgets was not attached to any parent then remove it here
    if (true == m_NeedDeleteStckedWidget)
    {
        delete this->m_pItemInfoViewWidgets;
    }
}

UIMainWindow::ItemInfoLayoutManager::ItemInfoLayoutManager(UIMainWindow & parent)
    : m_Parent(parent)
{
    m_pItemInfoViewWidgets = new QStackedWidget();

    this->createDefaultInfoLayout();
    this->createEmptyInfoLayout();

    m_pItemInfoViewWidgets->addWidget(this->m_pDefaultInfoWidget);
    m_pItemInfoViewWidgets->addWidget(this->m_pEmptyInfoWidget);

    this->connectUISignals();
}

void UIMainWindow::ItemInfoLayoutManager::setCurrentLayout(const InfoLayoutType type)
{
    switch (type)
    {
    case InfoLayoutType::ItemInfo :
        this->switchCurrentWidget(m_pDefaultInfoWidget);
        break;
    case InfoLayoutType::Empty :
        this->switchCurrentWidget(m_pEmptyInfoWidget);
        break;
    default:
        break;
    }
}

void UIMainWindow::ItemInfoLayoutManager::connectUISignals()
{
    QObject::connect(this->m_pSaveButton, &QPushButton::clicked,
                    [this](bool checked)
                    {
                        auto selIdx = m_Parent.m_pTreeView->selectionModel()->selection().indexes().at(0);
                        auto & selItem = TreeModel::GetInternalPointer(selIdx)->getUnderlaidData();

                        this->saveButtonAction(selItem, false /*this is an update action*/);
                    }
                    );
}

QStackedWidget *UIMainWindow::ItemInfoLayoutManager::getItemInfoViewWidgets()
{
    m_NeedDeleteStckedWidget = false;
    return this->m_pItemInfoViewWidgets;
}

void UIMainWindow::ItemInfoLayoutManager::createDefaultInfoLayout()
{
    m_pDefaultInfoWidget = new QWidget();
    m_pDefaultLayout = new QGridLayout();
        m_pDefaultLayout->setHorizontalSpacing(0);

    m_pDefaultInfoWidget->setLayout(m_pDefaultLayout);

    // common view testing
    m_pItemTypeLabel = new QLabel("Item type: ");

    // #######################################################
    // Create name input and its label
    m_pItemNameEdit = new QLineEdit();
    m_pItemNameEdit->setFrame(false);
    m_pItemNameEdit->setPlaceholderText("Item name");
    m_pItemNameEdit->setStyleSheet("background-color:White;");
    m_pItemNameEdit->setTextMargins(3,3,3,3);
        auto pNameLabel = new QLabel("<b>Name: </b>");
        pNameLabel->setMargin(3);
        pNameLabel->setStyleSheet("background-color:White;");
    //#######################################################

    //#######################################################
    // Create date -time edit for begin and end date
    m_pItemBeginDateEdit = new QDateTimeEdit();
    m_pItemBeginDateEdit->setToolTip("Begin date");
    m_pItemBeginDateEdit->setCalendarPopup(true);
    m_pItemBeginDateEdit->calendarWidget()->setGridVisible(true);

    m_pItemEndDateEdit = new QDateTimeEdit();
    m_pItemEndDateEdit->setToolTip("End date");
    m_pItemEndDateEdit->setCalendarPopup(true);
    m_pItemEndDateEdit->calendarWidget()->setGridVisible(true);



    //#######################################################
    // Create the text edit widget for description
    m_pItemDescrEdit = new QTextEdit();
    m_pItemDescrEdit->setPlaceholderText("Item description");
    //#######################################################

    //#######################################################
    // Create multiline label for additional info for selected item.
    // This is used only with project and timeinterval items, for task
    // item this is hidden.
    m_pAdditionalInfo = new QLabel();
//    m_pAdditionalInfo->hide();
    //#######################################################

    //#######################################################
    // Create combobox for task status and task priority
    m_pTaskStatusCombo = new QComboBox();
    m_pTaskStatusCombo->hide();
    for (const auto & i : TaskItem::STATE_STRINGS.keys())
    {
        m_pTaskStatusCombo->addItem(i);
    }

    m_pTaskPriorityCombo = new QComboBox();
    m_pTaskPriorityCombo->hide();
    for (const auto & i : TaskItem::PRIORITY_STRINGS.keys())
    {
        m_pTaskPriorityCombo->addItem(i);
    }
    //#######################################################


    //#######################################################
    // Create buttons
    m_pSaveButton = new QPushButton("Save");
    //#######################################################


    //#######################################################
    // Set widgets in layout

    m_pDefaultLayout->addWidget(m_pItemTypeLabel, 0, 0, 1, 1);


    m_pDefaultLayout->addWidget(m_pItemNameEdit, 1, 1, 1, 5);
    m_pDefaultLayout->addWidget(pNameLabel, 1, 0, 1, 1);

    m_pDefaultLayout->addWidget(m_pItemBeginDateEdit, 3, 0, 1, 3);
    m_pDefaultLayout->addWidget(m_pItemEndDateEdit, 3, 3, 1, 3);

    m_pDefaultLayout->addWidget(m_pAdditionalInfo, 5, 0, 2, 6);
    m_pDefaultLayout->addWidget(m_pTaskStatusCombo, 5, 0, 1, 2);
    m_pDefaultLayout->addWidget(m_pTaskPriorityCombo, 5, 3, 1, 2);

    m_pDefaultLayout->addWidget(m_pItemDescrEdit, 7, 0, 1, 6);

    m_pDefaultLayout->addWidget(m_pSaveButton, 8, 5, 1, 1);

    //#######################################################
}

void UIMainWindow::ItemInfoLayoutManager::createEmptyInfoLayout()
{
    m_pEmptyInfoWidget = new QWidget();
    m_pEmptyInfoLayout = new QGridLayout();

    m_pEmptyInfoWidget->setLayout(m_pEmptyInfoLayout);
}

void UIMainWindow::ItemInfoLayoutManager::switchCurrentWidget(QWidget *widget)
{
    if (nullptr == widget)
    {
        return;
    }

    // switch to requeted widget
    this->m_pItemInfoViewWidgets->setCurrentWidget(widget);
}

void UIMainWindow::ItemInfoLayoutManager::fillItemInfoLayout(const ProjectItemInterface & projItem, const QModelIndex & index)
{
    m_pItemTypeLabel->setText("Item type: <i>Project</i>");
    m_pItemNameEdit->setText(projItem.getName());
    m_pItemDescrEdit->setText(projItem.getDescription());

    auto dates = projItem.getDates();
    m_pItemBeginDateEdit->setDateTime(dates.first);
    m_pItemEndDateEdit->setDateTime(dates.second);

    // Show additional info Label
    m_pTaskStatusCombo->hide();
    m_pTaskPriorityCombo->hide();
    m_pAdditionalInfo->show();

    // read how many time intervals and tasks it has
    auto * treeItem = TreeModel::GetInternalPointer(index);
    size_t timeIntsCount = treeItem->childCount();

    size_t tasksCount = 0;
    for (size_t i = 0; i < timeIntsCount; ++i)
    {
        tasksCount += treeItem->child(i)->childCount();
    }

    m_pAdditionalInfo->setText(QString("Assigned time intervals: %1\n"
                                       "Total assigned tasks: %2")
                                        .arg(timeIntsCount)
                                        .arg(tasksCount)
                                      );
}

void UIMainWindow::ItemInfoLayoutManager::fillItemInfoLayout(const TimeIntervalInterface & timeintItem, const QModelIndex & index)
{
    m_pItemTypeLabel->setText("Item type: <i>Time interval</i>");
    m_pItemNameEdit->setText(timeintItem.getName());
    m_pItemDescrEdit->setText(timeintItem.getDescription());

    auto dates = timeintItem.getDates();
    m_pItemBeginDateEdit->setDateTime(dates.first);
    m_pItemEndDateEdit->setDateTime(dates.second);

    // Show additional info Label
    m_pTaskStatusCombo->hide();
    m_pTaskPriorityCombo->hide();
    m_pAdditionalInfo->show();

    // get tasks count
    auto * treeItem = TreeModel::GetInternalPointer(index);
    QString taskCount = QString::number(treeItem->childCount());
    m_pAdditionalInfo->setText(QString("Assigned tasks: ").append(taskCount));
}


void UIMainWindow::ItemInfoLayoutManager::fillItemInfoLayout(const TaskItemInterface & taskItem, const QModelIndex & index)
{
    m_pItemTypeLabel->setText("Item type: <i>Task</i>");
    m_pItemNameEdit->setText(taskItem.getName());
    m_pItemDescrEdit->setText(taskItem.getDescription());

    auto dates = taskItem.getDates();
    m_pItemBeginDateEdit->setDateTime(dates.first);
    m_pItemEndDateEdit->setDateTime(dates.second);

    // Hide additional info Label
    m_pAdditionalInfo->hide();
    m_pTaskStatusCombo->show();
    m_pTaskPriorityCombo->show();

    m_pTaskStatusCombo->setCurrentText(TaskItem::STATE_STRINGS.key(static_cast<TaskState>(taskItem.getState())));
    m_pTaskPriorityCombo->setCurrentText(TaskItem::PRIORITY_STRINGS.key(static_cast<TaskPriority>(taskItem.getPriority())));
}


void UIMainWindow::ItemInfoLayoutManager::commonSyncWithWidgets(ItemInterface & item)
{
    item.setName(m_pItemNameEdit->text());
    item.setDescription(m_pItemDescrEdit->toPlainText());
    item.setBeginDate(m_pItemBeginDateEdit->dateTime());
    item.setEndDate(m_pItemEndDateEdit->dateTime());
}

void UIMainWindow::ItemInfoLayoutManager::syncWithWidgets(ProjectItemInterface & proj)
{
    commonSyncWithWidgets(static_cast<ItemInterface&>(proj));
}

void UIMainWindow::ItemInfoLayoutManager::syncWithWidgets(TimeIntervalInterface & timeInt)
{
    commonSyncWithWidgets(static_cast<ItemInterface&>(timeInt));
}

void UIMainWindow::ItemInfoLayoutManager::syncWithWidgets(TaskItemInterface & task)
{
    // sync common part
    commonSyncWithWidgets(static_cast<ItemInterface &>(task));

    // sync custom data
    QString priorityText = m_pTaskPriorityCombo->currentText();
    task.setPriority(TaskItem::PRIORITY_STRINGS.value(priorityText));

    QString stateText = m_pTaskStatusCombo->currentText();
    task.setState(TaskItem::STATE_STRINGS.value(stateText));
}

// actions

void UIMainWindow::ItemInfoLayoutManager::saveButtonAction(ItemInterface & pItem, bool save)
{
    using namespace std;

    if (false == save)
    // update in data storage
    {
        try {
            m_Parent.m_SQLiteDBManager.open();

            // check for concrete item type
            if (typeid(ProjectItem) == typeid(pItem))
            {
                auto & pProjItem = static_cast<ProjectItemInterface&>(pItem);
                // Synchronize UI widgets data with underlaid object data
                syncWithWidgets(pProjItem);
                // update in database
                m_Parent.m_SQLiteDBManager.updateProject(pProjItem);
            }
            else if (typeid(TimeInterval) == typeid(pItem))
            {
                auto & pTimeItem = static_cast<TimeIntervalInterface&>(pItem);
                // Synchronize UI widgets data with underlaid object data
                syncWithWidgets(pTimeItem);
                // update in database
                m_Parent.m_SQLiteDBManager.updateTimeInterval(pTimeItem);
            }
            else if (typeid(TaskItem) == typeid(pItem))
            {
                auto & pTaskItem = static_cast<TaskItemInterface&>(pItem);
                // Synchronize UI widgets data with underlaid object data
                syncWithWidgets(pTaskItem);
                // update in database
                m_Parent.m_SQLiteDBManager.updateTaskItem(pTaskItem);
            }

            m_Parent.m_SQLiteDBManager.close();

            // Inform tree model view that data has been changed
            emit m_Parent.m_pTreeView->dataChanged(QModelIndex(), QModelIndex());

            m_Parent.statusBar()->showMessage("Update succeeded");
        }
        catch(...)
        {
            m_Parent.statusBar()->showMessage("Update failed");
        }
    }
    // Handle adding new item into database
    else
    {
        //TODO
    }

}
