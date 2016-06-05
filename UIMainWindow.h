#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QSplitter>
#include <QStackedWidget>

class UIMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit UIMainWindow(QWidget *parent = nullptr);

signals:

public slots:

private:
    void setupUI() ;


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
            Default,
            Task,
            TimeInterval,
            Project
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

        /**
         * @brief getItemInfoViewWidgets. It transfers the ownership.
         * @return
         */
        QStackedWidget * getItemInfoViewWidgets();

        // helper methods
    protected:
        void createDefaultInfoLayout();
        void createTaskInfoLayout();
        void createTimeIntervalInfoLayout();
        void createProjectInfoLayout();

        void switchCurrentWidget(QWidget * widget);

        // Members
    private:
        UIMainWindow & m_Parent;
        QStackedWidget * m_pItemInfoViewWidgets {nullptr};

        bool m_NeedDeleteStckedWidget {true};

        // Members for default layout - when none item is selected
    protected:
        QWidget * m_pDefaultInfoWidget;
        QGridLayout * m_pDefaultLayout;
        QLabel * m_pDefaultLabel {nullptr};

        // Members for layout to show task information layout
    protected:
        QWidget * m_pTaskInfoWidget;
        QGridLayout * m_pTaskLayout;
        QLabel * m_pTaskLabel {nullptr};

        // Memebers for layout to show time interval information
    protected:
        QWidget * m_pTimeIntervalInfoWidget;
        QGridLayout * m_pTimeIntLayout;
        QLabel * m_pTimeIntLabel {nullptr};

        // Members for layout to show project information
    protected:
        QWidget * m_pProjectInfoWidget;
        QGridLayout * m_pProjectLayout;
        QLabel * m_pProjectLabel {nullptr};

    };

private:
//    QGridLayout * m_pMainLayout {nullptr};

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
    QTreeWidget * m_pTreeWidget {nullptr};

//    // widget used for storing layouts for all available item 'views' (for default, project, task, time interval)
//    QStackedWidget * m_pInfoItemWidgets {nullptr};

    /// #######################################################################


    QLabel      * m_pLableOne {nullptr};


    ItemInfoLayoutManager m_ItemInfoLayoutManager;
};

#endif // UIMAINWINDOW_H
