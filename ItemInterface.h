#ifndef ITEMINTERFACE_H
#define ITEMINTERFACE_H

#include <utility> //std::pair
#include <memory>

class ItemInterface
{
public:
    using item_ptr_type = std::unique_ptr<ItemInterface>;

    ItemInterface() = default;
    virtual ~ItemInterface() = default;

    ItemInterface(const ItemInterface &) = default;
    ItemInterface & operator= (const ItemInterface &) = default;
    ItemInterface(ItemInterface &&) = default;
    ItemInterface & operator= (ItemInterface &&) = default;

    /**
    *   \brief          Provides way to change the begin date.
    *   \param beginDate    object which represents the begin date.
    */
    virtual void setBeginDate(QDateTime beginDate) = 0;

    /**
    *   \brief          Provides way to change the end date.
    *   \param endDate  object which represents the end date.
    */
    virtual void setEndDate(QDateTime endDate) = 0;

    /**
    *   \brief          Provides way to change new description.
    *   \param description  new description string which can not be empty.
    */
    virtual void setDescription(QString descr) = 0;

    /**
    *   \brief          Provides way to change new name.
    *   \param name     new name string which can not be empty.
    */
    virtual void setName(QString name) = 0;

    /**
    *   \brief          Return item begin and end dates.
    *   \return         Pair of begin and end date. The first is begin date. The second is end date.
    */
    virtual std::pair<QDateTime, QDateTime> getDates() const = 0;

    /**
    *   \brief          Return item description.
    *   \return         String which represents item description.
    */
    virtual QString getDescription() const = 0;

    /**
    *   \brief          Return name.
    *   \return         String which represents item name.
    */
    virtual QString getName() const = 0;

    /**
    *   \brief          Returns task ID. This ID represents the primary key in database.
    *   \return         Task ID.
    */
    virtual int     getID() const = 0;

};

#endif // ITEMINTERFACE_H
