#include "importsqlqueries.h"

#include <fstream>
#include <QDebug>

#include "loggingcategories.h"

#define LEN_STR 255

ImportSqlQueries::ImportSqlQueries()
{

}

void ImportSqlQueries::setConfigFile(QString fileName)
{
    qDebug(logInfo()) << "Starting to read file with SQL-Queries";
    lst.clear();
    try
    {
        std::ifstream in(fileName.toStdString());
        if (in.is_open())
        {
            char str[LEN_STR];
            std::string line, nameSqlQuery;
            int i = 0;
            while (getline(in, line))
            {
                if (sscanf(line.data(), "%s", str) == 1)
                {
                    switch (i)
                    {
                    case 0:
                        nameSqlQuery = line;
                        break;

                    case 1:
                        lst.append(QPair<QString, QString>(QString(nameSqlQuery.data()), QString(line.data())));
                        break;
                    }
                }

                i++;
                i %= 2;
            }
            in.close();
        }
        else
            throw "Unable to open file";

        qDebug(logInfo()) << "Reading file with SQL-Queries is successfull";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Unknown error! in " << __FILE__ << "Line: " << __LINE__ << endl;
    }
}

QList<QPair<QString, QString>> ImportSqlQueries::getList()
{
    return lst;
}

QList<QString> ImportSqlQueries::getListName()
{
    QList<QString> res;
    for (int i = 0; i < lst.size(); i++)
        res.append(lst[i].first);

    return res;
}

QList<QString> ImportSqlQueries::getListSqlQuery()
{
    QList<QString> res;
    for (int i = 0; i < lst.size(); i++)
        res.append(lst[i].second);

    return res;
}
