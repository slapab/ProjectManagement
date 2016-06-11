#ifndef ITEMINFOLAYOUTMANAGER_H
#define ITEMINFOLAYOUTMANAGER_H

#include <QObject>
#include <QStackedWidget>
#include "TaskItem.h"
#include "ProjectItem.h"
#include "TimeInterval.h"
#include <QLabel>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QCalendarWidget>

#include "TreeModel.h"

class QItemSelection;
class UIMainWindow;

/**
 * @brief The ItemInfoLayoutFactory class. This class is part of UI implementation.
 * It is strongly integrated with UIMainWindow class and this means it has to access
 * to UIMainWindow members and UIMainWindow has to access to this class members.
 */
class ItemInfoLayoutManager : public QObject
{
    Q_OBJECT
    /// Allow access from UIMainWindow to protected and private members.
    //friend class UIMainWindow;

public:
    enum class InfoLayoutType
    {
         ItemInfo
        ,Empty
    };

public:
    /**
     * @brief ItemInfoLayoutManager constructor.
     * @param parent    Need to has access to UIMainWindow members.
     */
    ItemInfoLayoutManager(UIMainWindow & parent);
    ~ItemInfoLayoutManager();
    /**
     * @brief           Changes the current layout if input parameter is recognized.
     * @param which     One of awaiable types.
     */
    void setCurrentLayout(const InfoLayoutType type);

    void connectUISignals();

    /**
     * @brief getItemInfoViewWidgets. It transfers the ownership.
     * @return
     */
    QStackedWidget * getItemInfoViewWidgets();


public slots:
    // prepares layout for adding new item depending on parent
    void treeContextCreateNewItemAction(const QModelIndex & index);
    void treeContextDeleteItemAction(const QModelIndex & index);
    void treeItemSelectedAction(const QItemSelection &selected, const QItemSelection &deselected);


    // helper methods
protected:
    void createDefaultInfoLayout();
    void createEmptyInfoLayout();
    void switchCurrentWidget(QWidget * widget);

    void syncWithWidgets(ProjectItemInterface & proj);
    void syncWithWidgets(TimeIntervalInterface & timeInt);
    void syncWithWidgets(TaskItemInterface & task);
    // Synchronize only common data
    void commonSyncWithWidgets(ItemInterface & item);

    void clearWidgetsData();
    void fillItemInfoLayout(const ProjectItemInterface & projItem, const QModelIndex & index);
    void fillItemInfoLayout(const TaskItemInterface & taskItem, const QModelIndex & index);
    void fillItemInfoLayout(const TimeIntervalInterface & timeIntItem, const QModelIndex & index);

    void saveButton_updateAction(ItemInterface & pItem);


    // Members for common item view layout
public:
    QLabel        * m_pItemTypeLabel {nullptr};
    QLineEdit     * m_pItemNameEdit {nullptr};
    QDateTimeEdit * m_pItemBeginDateEdit {nullptr};
    QDateTimeEdit * m_pItemEndDateEdit {nullptr};

    QLabel      * m_pAdditionalInfo {nullptr};
    QComboBox   * m_pTaskStatusCombo {nullptr};
    QComboBox   * m_pTaskPriorityCombo {nullptr};

    QTextEdit   * m_pItemDescrEdit {nullptr};

    QPushButton * m_pSaveButton {nullptr};

    // Members for default layout
protected:
    QGridLayout * m_pDefaultLayout;
    QWidget     * m_pDefaultInfoWidget;

    // Members for empty layout - when none item is selected
protected:
    QGridLayout * m_pEmptyInfoLayout;
    QWidget     * m_pEmptyInfoWidget;


    // Private Members
private:
    UIMainWindow & m_Parent;
    QStackedWidget * m_pItemInfoViewWidgets {nullptr};

    bool m_NeedDeleteStckedWidget {true};
    bool m_IsEditingItem {false};   //true when user selected item from tree, false if user wants to add new item
};

#endif // ITEMINFOLAYOUTMANAGER_H
