#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include "MyClasses/myqsqldatabase.h"

#define NUM_TRIES_TO_CONNECT 20

class Connection
{
    MyQSqlDatabase *db;
    QString typeDB;

public:
    Connection(bool need_to_init_db = true);
    Connection(QString type, QString nameDB, QString nameUser, QString host, QString password, int port);
    virtual ~Connection();
    virtual QSqlDatabase* getConnection();
    QString getTypeDB();
    QString getNameDB();
    int getPortDB();
    void setDB(MyQSqlDatabase *db);

    bool transaction();
    bool commit();
    bool rollback();

private:
    bool reconnect(int triesToConnect = 0);
};

#endif // CONNECTION_H
