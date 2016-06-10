#ifndef TREEITEMBASE_H
#define TREEITEMBASE_H

#include "TreeItemInterface.h"

//forward declarations:
class ProjectItemInterface;
class TaskItemInterface;
class TimeIntervalInterface;





class TreeItemBase : public TreeItemInterface
{
public:
    TreeItemBase(TreeItemInterface * parent);

    // TreeItemInterface interface
public:
    TreeItemInterface * child(int number) override;
    int childCount() const override;
    int columnCount() const override;
    int childNumber(const TreeItemInterface * const child) const override;
    TreeItemInterface * parent() override;

protected:
    TreeItemInterface * m_pParent {nullptr};
    std::vector<std::unique_ptr<TreeItemInterface>> m_Childs; // auto delete


};


//**
// * @brief The UniquePtrForQVariant class is using to pass std::unique_ptr reference(*) inside QVariant
// */
//template <class T>
//class UniquePtrForQVariant
//{
//public:
//    UniquePtrForQVariant()
//        : m_ptr{nullptr} {}
//    explicit UniquePtrForQVariant(const std::unique_ptr<T> & p)
//        : m_ptr{&p} {}

//    const std::unique_ptr<T> & getRef() throw(std::runtime_error)
//    {
//        if (nullptr == m_ptr)
//        {
//            throw std::runtime_error("UniquePtrForQVariant object hasn't valid address(nullptr)");
//        }
//        return *m_ptr;
//    }

//private:
//    const std::unique_ptr<T> * const m_ptr ;
//};

//Q_DECLARE_METATYPE(UniquePtrForQVariant<ProjectItemInterface>)
//Q_DECLARE_METATYPE(UniquePtrForQVariant<TaskItemInterface>)
//Q_DECLARE_METATYPE(UniquePtrForQVariant<TimeIntervalInterface>)


#endif // TREEITEMBASE_H
