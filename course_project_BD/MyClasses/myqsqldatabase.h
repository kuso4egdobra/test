#ifndef MYQSQLDATABASE_H
#define MYQSQLDATABASE_H

#include <QSqlDatabase>

class MyQSqlDatabase : public QSqlDatabase
{
public:
     MyQSqlDatabase();
     MyQSqlDatabase(QSqlDatabase db);

     virtual bool my_is_open();

//     MyQSqlDatabase &operator=(const QSqlDatabase &other);
};

#endif // MYQSQLDATABASE_H
