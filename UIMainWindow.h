#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTreeView>
#include <QSplitter>
#include <QStackedWidget>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>

#include "SQLiteAccess.h"

using namespace sql_data_storage;

class QItemSelection;

class UIMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIMainWindow(QWidget *parent = nullptr);

    ~UIMainWindow();

public:
    enum class SelectedItemType {Project, TimeInterval, Task, None};



private slots:
    void treeItemSelected(const QItemSelection &selected, const QItemSelection &deselected);

private:
    void setupUI() ;
    void connectUISignals();

    SelectedItemType whichItemSelected(const QModelIndex & index);

protected:
    /**
     * @brief The ItemInfoLayoutFactory class. This class is part of UI implementation.
     * It is strongly integrated with UIMainWindow class and this means it has to access
     * to UIMainWindow members and UIMainWindow has to access to this class members.
     */
    class ItemInfoLayoutManager
    {
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



        void fillItemInfoLayout(const ProjectItemInterface & projItem, const QModelIndex & index);
        void fillItemInfoLayout(const TaskItemInterface & taskItem, const QModelIndex & index);
        void fillItemInfoLayout(const TimeIntervalInterface & timeIntItem, const QModelIndex & index);

        void saveButtonAction(ItemInterface & pItem, bool save);


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

        // Members
    private:
        UIMainWindow & m_Parent;
        QStackedWidget * m_pItemInfoViewWidgets {nullptr};

        bool m_NeedDeleteStckedWidget {true};


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


    };

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
