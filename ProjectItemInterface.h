#ifndef PROJECTINTERFACE_H
#define PROJECTINTERFACE_H

#include <QDate>
#include <QString>

class ProjectItemInterface
{
public:
    ProjectItemInterface() = default;
    virtual ~ProjectItemInterface() {}

    virtual void setDate(const QDate date) = 0;
    virtual void setDescription(const QString descr) = 0;
    virtual void setName(const QString name) = 0;

    virtual QDate   getDate() const = 0;
    virtual QString getDescription() const = 0;
    virtual QString getName() const = 0;
};

#endif // PROJECTINTERFACE_H
