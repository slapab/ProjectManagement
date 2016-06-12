#include "ItemInfoLayoutManager.h"
#include <QStatusBar>
#include <QItemSelection>

#include "UIMainWindow.h"

ItemInfoLayoutManager::~ItemInfoLayoutManager()
{
    // If m_pItemInfoViewWidgets was not attached to any parent then remove it here
    if (true == m_NeedDeleteStckedWidget)
    {
        delete this->m_pItemInfoViewWidgets;
    }
}

ItemInfoLayoutManager::ItemInfoLayoutManager(UIMainWindow & parent)
    : m_Parent(parent)
{
    m_pItemInfoViewWidgets = new QStackedWidget();

    this->createDefaultInfoLayout();
    this->createEmptyInfoLayout();

    m_pItemInfoViewWidgets->addWidget(this->m_pDefaultInfoWidget);
    m_pItemInfoViewWidgets->addWidget(this->m_pEmptyInfoWidget);

    this->connectUISignals();
}

void ItemInfoLayoutManager::setCurrentLayout(const InfoLayoutType type)
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

void ItemInfoLayoutManager::connectUISignals()
{
    connect(this->m_pSaveButton, &QPushButton::clicked,
                    [this](bool checked)
                    {
                        auto selIdx = m_Parent.m_pTreeView->selectionModel()->selection().indexes().at(0);

                        if (true == m_IsEditingItem)
                        {
                            saveButton_updateAction(selIdx);
                        }
                        // creating new item
                        else
                        {
                            saveButton_saveNewAction(selIdx);
                        }
                    }
                    );
}

QStackedWidget * ItemInfoLayoutManager::getItemInfoViewWidgets()
{
    m_NeedDeleteStckedWidget = false;
    return this->m_pItemInfoViewWidgets;
}

void ItemInfoLayoutManager::createDefaultInfoLayout()
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

void ItemInfoLayoutManager::createEmptyInfoLayout()
{
    m_pEmptyInfoWidget = new QWidget();
    m_pEmptyInfoLayout = new QGridLayout();

    m_pEmptyInfoWidget->setLayout(m_pEmptyInfoLayout);
}

void ItemInfoLayoutManager::switchCurrentWidget(QWidget *widget)
{
    if (nullptr == widget)
    {
        return;
    }

    // switch to requeted widget
    this->m_pItemInfoViewWidgets->setCurrentWidget(widget);
}

void ItemInfoLayoutManager::fillItemInfoLayout(const ProjectItemInterface & projItem, const QModelIndex & index)
{
    m_pItemTypeLabel->setText("Item type: <b><i>Project</i></b>");
    m_pItemNameEdit->setText(projItem.getName());
    m_pItemDescrEdit->setText(projItem.getDescription());

    auto dates = projItem.getDates();
    m_pItemBeginDateEdit->setDateTime(dates.first);
    m_pItemEndDateEdit->setDateTime(dates.second);

    // Show additional info Label
    m_pTaskStatusCombo->hide();
    m_pTaskPriorityCombo->hide();
    m_pAdditionalInfo->show();

    if (false == index.isValid())
    {
        return;
    }

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

void ItemInfoLayoutManager::fillItemInfoLayout(const TimeIntervalInterface & timeintItem, const QModelIndex & index)
{
    m_pItemTypeLabel->setText("Item type: <b><i>Time interval</i></b>");
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
    if (false == index.isValid())
    {
        return;
    }
    auto * treeItem = TreeModel::GetInternalPointer(index);
    QString taskCount = QString::number(treeItem->childCount());
    m_pAdditionalInfo->setText(QString("Assigned tasks: ").append(taskCount));
}


void ItemInfoLayoutManager::fillItemInfoLayout(const TaskItemInterface & taskItem, const QModelIndex & index)
{
    m_pItemTypeLabel->setText("Item type: <b><i>Task</i></b>");
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


void ItemInfoLayoutManager::commonSyncWithWidgets(ItemInterface & item)
{
    item.setName(m_pItemNameEdit->text());
    item.setDescription(m_pItemDescrEdit->toPlainText());
    item.setBeginDate(m_pItemBeginDateEdit->dateTime());
    item.setEndDate(m_pItemEndDateEdit->dateTime());
}

void ItemInfoLayoutManager::syncWithWidgets(ProjectItemInterface & proj)
{
    commonSyncWithWidgets(static_cast<ItemInterface&>(proj));
}

void ItemInfoLayoutManager::syncWithWidgets(TimeIntervalInterface & timeInt)
{
    commonSyncWithWidgets(static_cast<ItemInterface&>(timeInt));
}

void ItemInfoLayoutManager::syncWithWidgets(TaskItemInterface & task)
{
    // sync common part
    commonSyncWithWidgets(static_cast<ItemInterface &>(task));

    // sync custom data
    QString priorityText = m_pTaskPriorityCombo->currentText();
    task.setPriority(TaskItem::PRIORITY_STRINGS.value(priorityText));

    QString stateText = m_pTaskStatusCombo->currentText();
    task.setState(TaskItem::STATE_STRINGS.value(stateText));
}

void ItemInfoLayoutManager::clearWidgetsData()
{
    m_pAdditionalInfo->clear();
    m_pItemBeginDateEdit->setDateTime(QDateTime::currentDateTime());
    m_pItemEndDateEdit->setDateTime(QDateTime::currentDateTime());
    m_pItemDescrEdit->clear();
    m_pItemNameEdit->clear();
    m_pItemTypeLabel->clear();
    m_pTaskPriorityCombo->setCurrentText(TaskItem::PRIORITY_STRINGS.key(TaskPriority::Normal));
    m_pTaskStatusCombo->setCurrentText(TaskItem::STATE_STRINGS.key(TaskState::Originated));
}



// actions:

void ItemInfoLayoutManager::saveButton_updateAction(const QModelIndex & index)
{
    using namespace std;

    auto & pItem = TreeModel::GetInternalPointer(index)->getUnderlaidData();
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


void ItemInfoLayoutManager::saveButton_saveNewAction(const QModelIndex & index)
{
    // get selected tree item
    auto treeItemIdx = m_Parent.m_pTreeView->selectionModel()->selectedIndexes().at(0);
    if (false == treeItemIdx.isValid())
    {
        return;
    }

    try
    {
        // Open database connection and insert new item
        m_Parent.m_SQLiteDBManager.open();

        if (TreeItemType::Project == m_CreatingItemType)
        {
            auto pNewProjectItem = m_Parent.m_SQLiteDBManager.addProject(
                                                   m_pItemNameEdit->text()
                                                 , m_pItemDescrEdit->toPlainText()
                                                 , m_pItemBeginDateEdit->dateTime()
                                                 , m_pItemEndDateEdit->dateTime()
                                                 );

            // Get the root tree item pointer
            auto * pProjTreeItem = TreeModel::GetInternalPointer(treeItemIdx);
            auto * rootItem = pProjTreeItem->parent();  // root must exists
            rootItem->createChild(std::move(pNewProjectItem));  // create new project item

        }
        else if (TreeItemType::TimeInterval == m_CreatingItemType)
        {
            auto * projTreeItem = TreeModel::GetInternalPointer(treeItemIdx);
            auto & projItem = projTreeItem->getUnderlaidData();

            auto pNewTimeInt = m_Parent.m_SQLiteDBManager.addTimeInterval(
                                                   projItem.getID()
                                                 , m_pItemNameEdit->text()
                                                 , m_pItemDescrEdit->toPlainText()
                                                 , m_pItemBeginDateEdit->dateTime()
                                                 , m_pItemEndDateEdit->dateTime()
                                                  );

            // add time interval to the selected project tree item
            projTreeItem->createChild(std::move(pNewTimeInt));
        }
        else if (TreeItemType::Task == m_CreatingItemType)
        {
            auto * timeTreeItem = TreeModel::GetInternalPointer(treeItemIdx);
            auto & timeItem = timeTreeItem->getUnderlaidData();

            auto priority = TaskItem::PRIORITY_STRINGS.value(m_pTaskPriorityCombo->currentText());
            auto state = TaskItem::STATE_STRINGS.value(m_pTaskStatusCombo->currentText());
            auto pNewTask = m_Parent.m_SQLiteDBManager.addTaskItem(
                                                   timeItem.getID()
                                                 , priority
                                                 , state
                                                 , m_pItemNameEdit->text()
                                                 , m_pItemDescrEdit->toPlainText()
                                                 , m_pItemBeginDateEdit->dateTime()
                                                 , m_pItemEndDateEdit->dateTime()
                                                  );

            timeTreeItem->createChild(std::move(pNewTask));
        }

        // Inform model about performed insertion of data
        if (TreeItemType::Project == m_CreatingItemType)
        {
            // Handle root item for project insertion
            m_Parent.m_pTreeView->model()->insertRows(0, 1, QModelIndex());
        }
        // handl rest item insersion
        else
        {
            m_Parent.m_pTreeView->model()->insertRows(0, 1, treeItemIdx);
        }

        // emit selection changed to refresh item layotu
        QItemSelection sel(treeItemIdx, treeItemIdx);
        emit m_Parent.m_pTreeView->selectionModel()->selectionChanged(sel, sel);

        m_Parent.statusBar()->showMessage("OK");
    }
    catch (std::exception & e)
    {
        //TODO log an error
        m_Parent.statusBar()->showMessage(QString("Adding new item failed: ").append(e.what()));
    }

    m_Parent.m_SQLiteDBManager.close();
}

// slot
void ItemInfoLayoutManager::treeContextCreateNewItemAction(TreeItemType createType)
{

    // After click on 'save' button the creating new item action should be performed
    m_IsEditingItem = false;
    // Store which type user want to create - it will be used in action method when user
    // click on the save button.
    m_CreatingItemType = createType;

    setCurrentLayout(InfoLayoutType::ItemInfo);
    clearWidgetsData();

    // Set appropratie type information and prepare layout for created item type
    QString t("Create new: <b><i>");
    auto currDate = QDateTime::currentDateTime();

    if (TreeItemType::Project == createType)
    {
        t.append("Project");
        ProjectItem p(0, "", "", currDate, currDate);
        fillItemInfoLayout(p, QModelIndex()); // prepare layout for project item
    }
    else if (TreeItemType::TimeInterval == createType)
    {
        TimeInterval tI(0, 0, "", "", currDate, currDate);
        fillItemInfoLayout(tI, QModelIndex()); // prepare layout for time interval item
        t.append("Time interval");
    }
    else if (TreeItemType::Task == createType)
    {
        TaskItem tTask(0, 0, TaskPriority::Normal, TaskState::Originated, "", "", currDate, currDate);
        fillItemInfoLayout(tTask, QModelIndex()); // Prepare layout for task item
        t.append("Task");
    }
    t.append("</i></b>");
    m_pItemTypeLabel->setText(t);

}

// slot
void ItemInfoLayoutManager::treeContextDeleteItemAction(const QModelIndex & index)
{
//    m_Parent.statusBar()->showMessage(QString("Deleting ").append(index.data(0).toString()));
    if (false == index.isValid())
    {
        return;
    }

    auto * treeItem = TreeModel::GetInternalPointer(index);

    if (nullptr == treeItem)
    {
        return;
    }

    try
    {
        m_Parent.m_SQLiteDBManager.open();

        const TreeItemType itemType = treeItem->getType();
        if (TreeItemType::Project == itemType)
        {
            auto & proj = static_cast<ProjectItemInterface&>(treeItem->getUnderlaidData());
            m_Parent.m_SQLiteDBManager.removeProjectItem(proj);
        }
        else if (TreeItemType::TimeInterval == itemType)
        {
            auto & timeInt = static_cast<TimeIntervalInterface&>(treeItem->getUnderlaidData());
            m_Parent.m_SQLiteDBManager.removeTimeInterval(timeInt);
        }
        else if (TreeItemType::Task == itemType)
        {
            auto & task = static_cast<TaskItemInterface&>(treeItem->getUnderlaidData());
            m_Parent.m_SQLiteDBManager.removeTaskItem(task);
        }

        // Remove item from tree model
        int childRow = treeItem->parent()->childNumber(treeItem);
        m_Parent.m_pTreeView->model()->removeRows(childRow, 1, index.parent());

    }
    catch(...)
    {}

    m_Parent.m_SQLiteDBManager.close();
}

// slot
void ItemInfoLayoutManager::treeItemSelectedAction(const QItemSelection &selected, const QItemSelection &)
{
    auto index = selected.indexes().at(0);

    if (false == index.isValid())
    {
        return;
    }

    // After click to "save" button the update should be performed
    m_IsEditingItem = true;

    // set current layout to item view layout
    setCurrentLayout(ItemInfoLayoutManager::InfoLayoutType::ItemInfo);

    auto * pTreeItemI = TreeModel::GetInternalPointer(index);
    auto type = pTreeItemI->getType();

    if (TreeItemType::Project == type)
    {
        auto & item = dynamic_cast<ProjectItemInterface &>(pTreeItemI->getUnderlaidData());

        fillItemInfoLayout(item, index);
    }
    else if (TreeItemType::TimeInterval == type)
    {
        auto & item = dynamic_cast<TimeIntervalInterface &>(pTreeItemI->getUnderlaidData());

        fillItemInfoLayout(item, index);
    }
    else if (TreeItemType::Task == type)
    {
        auto & item = dynamic_cast<TaskItemInterface &>(pTreeItemI->getUnderlaidData());

        fillItemInfoLayout(item, index);
    }
}
