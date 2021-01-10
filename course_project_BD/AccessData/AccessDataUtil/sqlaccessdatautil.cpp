#include "sqlaccessdatautil.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>

#include "AccessData/QueryGenerator/psgrequerygenerator.h"
#include "loggingcategories.h"

SqlAccessDataUtil::SqlAccessDataUtil()
{
    connection = new Connection;
    access = new AccessToDB;
    needToColorOldDocs = false;
}

SqlAccessDataUtil::SqlAccessDataUtil(AccessToDB *access)
{
    connection = new Connection;
    this->access = access;
    needToColorOldDocs = false;
}

SqlAccessDataUtil::~SqlAccessDataUtil()
{
    if (connection)
        delete connection;

//    if (access)
//        delete access;
}

QSqlQueryModel* SqlAccessDataUtil::getData(QString &queryString)
{
    QSqlQueryModel* model = nullptr;
    QSqlDatabase *db = nullptr;
    try
    {
        db = connection->getConnection();
        if (!db)
            throw -1;

        MyQSqlQuery query = MyQSqlQuery(*db);
        query.prepare(queryString);
        model = access->getData(query);
    }
    catch (...)
    {
        qDebug(logCritical()) << "Unknown error! in " << __FILE__ << "Line: " << __LINE__ << endl;
        model = nullptr;
    }

    return model;
}

QSqlRelationalTableModel* SqlAccessDataUtil::select(QString &tableName)
{
    QSqlRelationalTableModel *model = nullptr;
    QSqlDatabase *db = nullptr;
    try
    {
        db = connection->getConnection();
        if (!db || !checkValidTableName(tableName))
            throw -1;

        model = new QSqlRelationalTableModel(nullptr, *db);
        model->setTable(tableName);
        access->select(model);
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error select" << __FILE__ << "Line: " << __LINE__ << endl;
        return nullptr;
    }

     return model;
}

bool SqlAccessDataUtil::setData(QSqlRelationalTableModel &model)
{
    return access->setData(model);
}

MyQSqlQueryModel* SqlAccessDataUtil::run(const QString &sqlString)
{
    QSqlDatabase *db = nullptr;
    MyQSqlQueryModel *model = new MyQSqlQueryModel(needToColorOldDocs);

    try
    {
        db = connection->getConnection();
        if (!db)
            throw -1;

        MyQSqlQuery query = MyQSqlQuery(*db);
        query.prepare(sqlString);
        access->run(query);
        model->setQuery(query);
    }
    catch(...)
    {
        qDebug(logCritical()) << "Error running sql request as admin\n";
    }

    return model;
}

int SqlAccessDataUtil::insert(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue)
{
    QSqlDatabase *db = nullptr;
    int res = 0;
    try
    {
        db = connection->getConnection();
        if (!db || !checkValidTableName(tableName))
            throw -1;

        MyQSqlQuery query = MyQSqlQuery(*db);
        QString type = connection->getTypeDB();
        if (type == "QPSQL")
        {
            PsgreQueryGenerator querygen;
            query.prepare(querygen.insert(tableName, atributesName, atributesValue));
        }
        else
            throw -2;

        res = access->insert(query);
    }
    catch (int err)
    {
        switch (err)
        {
        case -1:
        {
            qDebug(logCritical()) << "Error in insert connecting to db or invalid tableName";
            res = -1;
            break;
        }
        case -2:
        {
            qDebug(logCritical()) << "Error in insert, unknown type DB";
            res = -2;
            break;
        }
        default:
        {
            qDebug(logCritical()) << "unknown error in insert";
            res = -3;
        }
        }
    }
    catch (...)
    {
         qDebug(logCritical()) << "unknown error in insert" << __FILE__ << "Line: " << __LINE__ << endl;
         res = -4;
    }

    return res;
}

int SqlAccessDataUtil::update(const QString &tableName, int idUpdate, const QStringList &atributesName, const QStringList &atributesValue)
{
    QSqlDatabase *db = nullptr;
    int res = 0;
    try
    {
        db = connection->getConnection();
        if (!db || !checkValidTableName(tableName))
            throw -1;

        MyQSqlQuery query = MyQSqlQuery(*db);
        QString type = connection->getTypeDB();
        if (type == "QPSQL")
        {
            PsgreQueryGenerator querygen;
            query.prepare(querygen.update(tableName, idUpdate, atributesName, atributesValue));
        }
        else
            throw -2;

        res = access->update(query);
    }
    catch (int err)
    {
        switch (err)
        {
        case -1:
        {
            qDebug(logCritical()) << "Error in update connecting to db or invalid tableName";
            res = -1;
            break;
        }
        case -2:
        {
            qDebug(logCritical()) << "Error in update, unknown type DB";
            res = -2;
            break;
        }
        default:
        {
            qDebug(logCritical()) << "unknown error in update";
            res = -3;
        }
        }
    }
    catch (...)
    {
        qDebug(logCritical()) << "unknown error in update" << __FILE__ << "Line: " << __LINE__ << endl;
        res = -4;
    }

    return res;
}

QStringList SqlAccessDataUtil::getSamePeople(QString tableName, int idPersonNotInclude, QString sameColumnName, QString sameColumnValue)
{
    QSqlDatabase *db = nullptr;
    QStringList lst;
    int res = 0;
    try
    {
        db = connection->getConnection();
        if (!db || !checkValidTableName(tableName))
            throw -1;

        MyQSqlQuery query = MyQSqlQuery(*db);
        QString type = connection->getTypeDB();
        if (type == "QPSQL")
        {
            PsgreQueryGenerator querygen;
            query.prepare(querygen.getSamePeople(tableName, idPersonNotInclude, sameColumnName, sameColumnValue));
        }
        else
            throw -2;

        access->run(query);
        while (query.next())
        {
            qDebug() << query.record();
            lst.append(QString(QString::number(query.record().value(0).toInt())));
        }
    }
    catch (int err)
    {
        switch (err)
        {
        case -1:
        {
            qDebug(logCritical()) << "Error in getSamePeople connecting to db or invalid tableName";
            res = -1;
            break;
        }
        case -2:
        {
            qDebug(logCritical()) << "Error in getSamePeople, unknown type DB";
            res = -2;
            break;
        }
        default:
        {
            qDebug(logCritical()) << "unknown error in getSamePeople";
            res = -3;
        }
        }
    }
    catch (...)
    {
        qDebug(logCritical()) << "unknown error in getSamePeople" << __FILE__ << "Line: " << __LINE__ << endl;
        res = -4;
    }

    return lst;
}

bool SqlAccessDataUtil::transaction()
{
    return connection->transaction();
}

bool SqlAccessDataUtil::commit()
{
    return connection->commit();
}

bool SqlAccessDataUtil::rollback()
{
    return connection->rollback();
}

void SqlAccessDataUtil::setFlagNeedToColorOldDocs(bool flag)
{
    needToColorOldDocs = flag;
}

void SqlAccessDataUtil::setConnection(Connection *connection)
{
    delete this->connection;
    this->connection = connection;
}

//void SqlAccessDataUtil::doBackUP()
//{
//    QSqlDatabase *db = nullptr;
//    try
//    {
//        db = connection->getConnection();
//        if (!db)
//            throw -1;
//        QStringList tables = connection->getConnection()->tables();
//        for (int i = 0; i < tables.size(); i++)
//        {
//            QSqlQuery query = QSqlQuery(*db);
//            QString type = connection->getTypeDB();
//            if (type == "QPSQL")
//            {
//                PsgreQueryGenerator querygen;
//                query.prepare(querygen.backUP(tables[i]));
//            }
//            else
//                throw -2;

//            access->run(query);
//        }
//    }
//    catch(...)
//    {
//        qDebug() << "Error doing backup" << __FILE__ << "Line: " << __LINE__ << endl;;
//    }
//}

bool SqlAccessDataUtil::checkValidTableName(const QString &tableName)
{
    QStringList tables;
    try
    {
        tables = connection->getConnection()->tables();
        if (tables.size() < 1)
            return true;
//            throw -1;
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error unable to recieve table names" << __FILE__ << "Line: " << __LINE__ << endl;;
        return false;
    }

    bool isFound = false;
    for (int i = 0; i < tables.size() && !isFound; i++)
        if (tables[i] == tableName)
            isFound = true;

    return isFound;
}

