#ifndef ACCESSTODB_H
#define ACCESSTODB_H

#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

#include "MyClasses/myqsqlquery.h"


class AccessToDB
{

public:
    AccessToDB();

    // work with Model
    QSqlQueryModel* getData(MyQSqlQuery &query);
    void select(QSqlRelationalTableModel *model);
    bool setData(QSqlRelationalTableModel &model);
    virtual void run(MyQSqlQuery &query);

    virtual int insert(MyQSqlQuery &query);
    int update(MyQSqlQuery &query);

private:
    bool checkValidTableName(const QString &tableName);
};

#endif // ACCESSTODB_H
