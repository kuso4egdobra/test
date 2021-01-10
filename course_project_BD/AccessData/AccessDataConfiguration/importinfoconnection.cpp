#include "importinfoconnection.h"

#include <fstream>
#include <QStringList>
#include <QDebug>

#define LEN_STR 255

ImportInfoConnection::ImportInfoConnection(QString fileName)
{
    try
    {
        std::ifstream in(fileName.toStdString());
        if (in.is_open())
        {
            char str[LEN_STR];
            std::string line;
            int i = 0;
            while (getline(in, line))
            {
                if (sscanf(line.data(), "%s", str) == 1)
                {
                    switch (i) // номер строки
                    {
                    case 0:
                        typeDatabase = str;
                        break;

                    case 1:
                        hostName = str;
                        break;

                    case 2:
                        databaseName = str;
                        break;

                    case 3:
                        userName = str;
                        break;

                    case 4:
                        password = str;
                        break;

                    case 5:
                        port = str;
                        break;
                    }
                }

                i++;
            }
            in.close();

            if (i != 6)
                throw "Wrong size of file";
        }
        else
            throw "Unable to open file";
    }
    catch (char const* str)
    {
        qDebug() << str << " in " << __FILE__ << "Line: " << __LINE__ << endl;
    }
    catch (...)
    {
        qDebug() << "Unknown error! in " << __FILE__ << "Line: " << __LINE__ << endl;
    }
}

QStringList ImportInfoConnection::getInfoConnection()
{
    return QStringList({typeDatabase, hostName, databaseName, userName, password, port});
}

QString ImportInfoConnection::getTypeDatabase()
{
    return typeDatabase;
}

QString ImportInfoConnection::getHostName()
{
    return hostName;
}

QString ImportInfoConnection::getDatabaseName()
{
    return databaseName;
}

QString ImportInfoConnection::getUserName()
{
    return userName;
}

QString ImportInfoConnection::getPassword()
{
    return password;
}

QString ImportInfoConnection::getPort()
{
    return port;
}
