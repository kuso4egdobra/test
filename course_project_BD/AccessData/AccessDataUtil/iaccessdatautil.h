#ifndef IACCESSDATAUTIL_H
#define IACCESSDATAUTIL_H

#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

class IAccessDataUtil
{

public:
    virtual ~IAccessDataUtil();
    virtual QSqlQueryModel* getData(QString &queryString) = 0;
    virtual QSqlRelationalTableModel* select(QString &tableName) = 0;
    virtual bool setData(QSqlRelationalTableModel &model) = 0;
    virtual QSqlQueryModel* run(const QString &sqlString) = 0;

    virtual int insert(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue) = 0;
    virtual int update(const QString &tableName, int idUpdate, const QStringList &atributesName, const QStringList &atributesValue)= 0;
};

#endif // IACCESSDATAUTIL_H
