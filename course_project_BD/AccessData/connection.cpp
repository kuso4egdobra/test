#include "connection.h"
#include "AccessDataConfiguration/accessdataconfiguration.h"
#include "AccessDataConfiguration/importinfoconnection.h"

#include <QDebug>
#include <QSqlError>

#include "../loggingcategories.h"

Connection::Connection(bool need_to_init_db)
{
    if (need_to_init_db)
    {
        AccessDataConfiguration config;
        ImportInfoConnection *info = config.getConfiguration();
        db = new MyQSqlDatabase(QSqlDatabase::addDatabase(info->getTypeDatabase()));
        db->setHostName(info->getHostName());
        db->setDatabaseName(info->getDatabaseName());
        db->setUserName(info->getUserName());
        db->setPassword(info->getPassword());
        db->setPort(info->getPort().toInt());

        typeDB = info->getTypeDatabase();

        reconnect();
    }
}

Connection::Connection(QString type, QString nameDB, QString nameUser,
                       QString host, QString password, int port) : Connection()
{

}

Connection::~Connection()
{
    if (db->isOpen())
        db->close();
}

QSqlDatabase* Connection::getConnection()
{
    QSqlDatabase* res = db;
    try
    {
        if (!db->my_is_open())
            reconnect();

        if (!db->my_is_open())
            throw -1;
    }
    catch (...)
    {
        qDebug(logCritical()) << "Unable to connect to DB" << __FILE__ << "Line: " << __LINE__ << endl;
        res = nullptr;
    }

    return res;
}

QString Connection::getTypeDB()
{
    return db->driverName();
}

QString Connection::getNameDB()
{
    return db->databaseName();
}

int Connection::getPortDB()
{
    return db->port();
}

bool Connection::transaction()
{
    return db->transaction();
}

bool Connection::commit()
{
    return db->commit();
}

bool Connection::rollback()
{
    return db->rollback();
}

bool Connection::reconnect(int triesToConnect)
{
    bool isSuccess = true;
    try
    {
        db->open();
        if (!db->my_is_open())
            throw -1;
        qDebug(logInfo()) << "Connection is open";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Trying to connect to DB..." << db->lastError() << "Num try: " << triesToConnect
                              << __FILE__ << "Line: " << __LINE__ << endl;
        isSuccess = false;
    }

    return (triesToConnect++ < NUM_TRIES_TO_CONNECT && !isSuccess) ? reconnect(triesToConnect) : isSuccess;
}

void Connection::setDB(MyQSqlDatabase *db)
{
    this->db = db;
}
