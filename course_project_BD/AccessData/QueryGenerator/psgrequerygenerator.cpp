#include "psgrequerygenerator.h"

#include <QStringList>
#include <QDebug>

#include "../../loggingcategories.h"

QString listAtributes(const QStringList &list)
{
    QString resString("(");
    for (int i = 0; i < list.size() - 1; i++)
    {
        resString += list[i] + ", ";
    }
    resString += list[list.size() - 1] + ")";

    return resString;
}

PsgreQueryGenerator::PsgreQueryGenerator()
{

}

QString PsgreQueryGenerator::insert(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue)
{
    if (
            !tableName.size() ||
            !atributesName.size() ||
            !atributesValue.size() ||
            atributesName.size() != atributesValue.size()
       )
        return QString("");

    QString str = QString("INSERT INTO "
                          + tableName
                          + " "
                          + listAtributes(atributesName)
                          + " VALUES "
                          + listAtributes(atributesValue)
                          + " RETURNING id;");
    qDebug(logInfo()) << "SQL-Query: " << str;
    return str;
}

QString PsgreQueryGenerator::update(const QString &tableName, int idUpdate, const QStringList &atributesName, const QStringList &atributesValue)
{
    if (
            !tableName.size() ||
            !atributesName.size() ||
            !atributesValue.size() ||
            atributesName.size() != atributesValue.size()
       )
        return QString("");

    QString str = QString("UPDATE "
                          + tableName
                          + " SET "
                          + listAtributes(atributesName)
                          + " = "
                          + listAtributes(atributesValue)
                          + " WHERE id = " // можно сделать универсальней, передавая атрибуты для where
                          + QString(QString::number(idUpdate))
                          + ";");
    qDebug(logInfo()) << "SQL-Query: " << str;
    return str;
}

QString PsgreQueryGenerator::select()
{
    return "";
}

QString PsgreQueryGenerator::getSamePeople(QString &tableName, int idPersonNotInclude, QString &sameColumnName, QString &sameColumnValue)
{
    QString str = QString("select p.id from (("
                   + tableName
                   + " left join document d on "
                   + tableName
                   + ".id_doc = d.id) left join person p on d.id_person = p.id) where p.id != "
                   + QString(QString::number(idPersonNotInclude))
                   + " and "
                   + tableName
                   + "."
                   + sameColumnName
                   + " = '"
                   + sameColumnValue
                   + "';");
    qDebug(logInfo()) << "SQL-Query: " << str;
    return str;
}

//QString PsgreQueryGenerator::backUP(const QString &table)
//{
//    QString str;
////    for (int i = 0; i < tables.size(); i++)
//        str += "copy (select array_to_json(array_agg(row_to_json("
//                + table
//                + "))) from "
//                + table
//                + ") to '/tmp/"
//                + table
//                + ".json';";
//        qDebug() << str << endl;
//    return str;
//}

