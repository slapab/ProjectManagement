#ifndef PROJECTINTERFACE_H
#define PROJECTINTERFACE_H

#include <QDate>
#include <QString>

class ProjectItemInterface
{
public:
    ProjectItemInterface() = default;
    virtual ~ProjectItemInterface() {}

    virtual void setDate(QDate date) = 0;
    virtual void setDescription(QString descr) = 0;
    virtual void setName(QString name) = 0;

    virtual QDate   getDate() const = 0;
    virtual QString getDescription() const = 0;
    virtual QString getName() const = 0;
};

#endif // PROJECTINTERFACE_H
