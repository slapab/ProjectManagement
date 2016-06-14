### About project

ProjectManagement is simple application written in C\+\+11 and Qt5 which will help to manage work on projects you're working on.

The main reason to create this application was desire to learn the Qt 5 library and improve own skills in C++11 and checks its features. As data storage the SQLite (version 3) is using with foreign keys enabled. 

Current sources were developed only on Linux, but Qt is multi platform library and in sources there are no any Linux dependent functionality.

### Branching convention:
- **master** – branch were will be sources (merged from ***int*** only) of fully working code, but not only stable releases - these will be marked with tags
- **int** – the integration branch, here always should be source code which compiles without any errors and application starts without crash
- **developing branches** – branches used to store sources during any development (new functionality, bug fix, etc.). If changes were tested then they should be merged into ***int*** branch


### What has already done?

- user is able to add (context menu) new project, new time interval into project and new task into given time interval
- user is able to delete (context menu) selected project (with its time intervals and tasks), selected timer interval (with its tasks) and selected task
- user is able to display information about each selected item (project, time interval, task)
- user is able to update any information of selected item

### What should be done in near future?

- user should be able to select database file. Currently, database file is storing in application directory
- begin and end time of time intervals and tasks should be narrowed to the range defined by parent item
- visual distinguish of each project in thre tree view – for example use different colors (maybe user defined)
