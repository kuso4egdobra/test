#include "myqsqldatabase.h"

MyQSqlDatabase::MyQSqlDatabase()
{

}

MyQSqlDatabase::MyQSqlDatabase(QSqlDatabase db) : QSqlDatabase (db)
{

}

bool MyQSqlDatabase::my_is_open()
{
    return isOpen();
}

//MyQSqlDatabase &MyQSqlDatabase::operator=(const QSqlDatabase &other)
//{
//    this = MyQSqlDatabase(other);
//}
