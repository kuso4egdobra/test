#ifndef IMPORTINFOCONNECTION_H
#define IMPORTINFOCONNECTION_H

#include <QString>

class ImportInfoConnection
{
    QString typeDatabase;
    QString hostName;
    QString databaseName;
    QString userName;
    QString password;
    QString port;

public:
    ImportInfoConnection(QString fileName);
    QStringList getInfoConnection();
    QString getTypeDatabase();
    QString getHostName();
    QString getDatabaseName();
    QString getUserName();
    QString getPassword();
    QString getPort();
};

#endif // IMPORTINFOCONNECTION_H
