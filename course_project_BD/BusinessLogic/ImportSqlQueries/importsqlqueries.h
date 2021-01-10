#ifndef IMPORTSQLQUERIES_H
#define IMPORTSQLQUERIES_H

#include <QList>

class ImportSqlQueries
{
    QList<QPair<QString, QString>> lst;

public:
    ImportSqlQueries();

    void setConfigFile(QString fileName);
    QList<QPair<QString, QString>> getList();
    QList<QString> getListName();
    QList<QString> getListSqlQuery();

};

#endif // IMPORTSQLQUERIES_H
