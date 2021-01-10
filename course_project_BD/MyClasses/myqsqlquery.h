#ifndef MYQSQLQUERY_H
#define MYQSQLQUERY_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>

class MyQSqlQuery : public QSqlQuery
{
public:
     MyQSqlQuery();
     MyQSqlQuery(QSqlDatabase db);

     virtual bool my_exec();
     virtual bool my_next();
     virtual QSqlRecord my_record() const;

};

#endif // MYQSQLQUERY_H
