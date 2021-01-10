#include "myqsqlquery.h"

MyQSqlQuery::MyQSqlQuery()
{

}

MyQSqlQuery::MyQSqlQuery(QSqlDatabase db) : QSqlQuery (db)
{

}

bool MyQSqlQuery::my_exec()
{
    return exec();
}

bool MyQSqlQuery::my_next()
{
    return next();
}

QSqlRecord MyQSqlQuery::my_record() const
{
    return record();
}
