#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include "ProjectItemInterface.h"

class ProjectItem : public virtual ProjectItemInterface
{
public:
    ProjectItem();
    ProjectItem(QString name, QDate date);
    ProjectItem(QString name, QString descr, QDate date);

    virtual ~ProjectItem();

    void setDate(QDate date) override;
    void setDescription(QString descr) override;
    void setName(QString name) override;

    QDate   getDate() const override;
    QString getDescription() const override;
    QString getName() const override;

protected:
    QString m_Name;
    QString m_Description;
    QDate   m_CreationDate;
};

#endif // PROJECTITEM_H
