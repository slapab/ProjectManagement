#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include "ProjectItemInterface.h"

class ProjectItem : public virtual ProjectItemInterface
{
public:
    ProjectItem();
    ProjectItem(const QString name, const QDate date);
    ProjectItem(const QString name, const QString descr, const QDate date);

    virtual ~ProjectItem();

    void setDate(const QDate date) override;
    void setDescription(const QString descr) override;
    void setName(const QString name) override;

    QDate   getDate() const override;
    QString getDescription() const override;
    QString getName() const override;

protected:
    QString m_Name;
    QString m_Description;
    QDate   m_CreationDate;
};

#endif // PROJECTITEM_H
