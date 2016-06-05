#include "UIMainWindow.h"
#include <memory> // std::unique_ptr

UIMainWindow::UIMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ItemInfoLayoutManager(*this)
{
    this->setupUI();
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

    this->setGeometry(100,100, 300,300);

    // #######################################
    // Create and prepare layout to store:
    // tree widget on the left and layouts (on the right) to present information about selected item
    m_pDataLayout = new QHBoxLayout();
    // add this sub-layout to the main layout
    m_pMainLayout->addLayout(m_pDataLayout);

    m_pDataSplitter = new QSplitter();
    m_pDataLayout->addWidget(m_pDataSplitter);

    m_pTreeWidget = new QTreeWidget();
    // appned tree widget and info layout to the splitter
    m_pDataSplitter->addWidget(m_pTreeWidget);

    // append item info view widget to right space of splitter
    m_pDataSplitter->addWidget(m_ItemInfoLayoutManager.getItemInfoViewWidgets());
    // Set item info layout to default
    m_ItemInfoLayoutManager.setCurrentLayout(ItemInfoLayoutManager::InfoLayoutType::Default);

    // #######################################


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
    this->createProjectInfoLayout();
    this->createTaskInfoLayout();
    this->createTimeIntervalInfoLayout();

    m_pItemInfoViewWidgets->addWidget(this->m_pDefaultInfoWidget);
    m_pItemInfoViewWidgets->addWidget(this->m_pProjectInfoWidget);
    m_pItemInfoViewWidgets->addWidget(this->m_pTaskInfoWidget);
    m_pItemInfoViewWidgets->addWidget(this->m_pTimeIntervalInfoWidget);
}

void UIMainWindow::ItemInfoLayoutManager::setCurrentLayout(const InfoLayoutType type)
{
    switch (type)
    {
    case InfoLayoutType::Default :
        this->switchCurrentWidget(m_pDefaultInfoWidget);
        break;
    case InfoLayoutType::Task :
        this->switchCurrentWidget(m_pTaskInfoWidget);
        break;
    case InfoLayoutType::Project:
        this->switchCurrentWidget(m_pProjectInfoWidget);
        break;
    case InfoLayoutType::TimeInterval:
        this->switchCurrentWidget(m_pTimeIntervalInfoWidget);
        break;
    default:
        break;
    }
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

    m_pDefaultInfoWidget->setLayout(m_pDefaultLayout);

    m_pDefaultLabel = new QLabel("Defaultowa labeleczka");
    m_pDefaultLayout->addWidget(m_pDefaultLabel,0,1,1,2);

    //todo implement rest
}

void UIMainWindow::ItemInfoLayoutManager::createTaskInfoLayout()
{
    m_pTaskInfoWidget = new QWidget();
    m_pTaskLayout = new QGridLayout();

    m_pTaskInfoWidget->setLayout(m_pTaskLayout);

    //TODO implement the rest
}

void UIMainWindow::ItemInfoLayoutManager::createTimeIntervalInfoLayout()
{
    m_pTimeIntervalInfoWidget = new QWidget();
    m_pTimeIntLayout = new QGridLayout();

    m_pTimeIntervalInfoWidget->setLayout(m_pTimeIntLayout);

    //TODO implement the rest
}

void UIMainWindow::ItemInfoLayoutManager::createProjectInfoLayout()
{
    m_pProjectInfoWidget = new QWidget();
    m_pProjectLayout = new QGridLayout();

    m_pProjectInfoWidget->setLayout(m_pProjectLayout);

    m_pProjectLabel = new QLabel("Projektu labelka");
    m_pProjectLayout->addWidget(m_pProjectLabel, 1, 1, 1, 2);

    //TODO implement rest
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
