#ifndef SQLACCESSDATAUTIL_H
#define SQLACCESSDATAUTIL_H


#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlDatabase>

#include "iaccessdatautil.h"
#include "AccessData/connection.h"
#include "AccessData/accesstodb.h"

#include "MyClasses/myqsqlquery.h"
#include "MyClasses/myqsqlquerymodel.h"

class SqlAccessDataUtil : IAccessDataUtil
{
    Connection *connection;
    AccessToDB *access;
    bool needToColorOldDocs;

public:
    SqlAccessDataUtil();
    SqlAccessDataUtil(AccessToDB*);
    ~SqlAccessDataUtil() override;

    // work with Model
    QSqlQueryModel* getData(QString &queryString) override;
    QSqlRelationalTableModel* select(QString &tableName) override;
    bool setData(QSqlRelationalTableModel &model) override;
    MyQSqlQueryModel* run(const QString &sqlString) override;

    virtual int insert(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue) override;
    virtual int update(const QString &tableName, int idUpdate, const QStringList &atributesName,
               const QStringList &atributesValue) override;

    QStringList getSamePeople(QString tableName, int idPersonNotInclude, QString sameColumnName, QString sameColumnValue);

    virtual bool transaction();
    virtual bool commit();
    virtual bool rollback();
    void setFlagNeedToColorOldDocs(bool flag);
    void setConnection(Connection* connect);

private:
    bool checkValidTableName(const QString &tableName);

};

#endif // SQLACCESSDATAUTIL_H
