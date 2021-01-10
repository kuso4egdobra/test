#ifndef IQUERYGENERATOR_H
#define IQUERYGENERATOR_H

#include <QString>

class IQueryGenerator
{
public:
    IQueryGenerator();
    virtual ~IQueryGenerator();
    virtual QString insert(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue) = 0;
    virtual QString update(const QString &tableName, int idUpdate, const QStringList &atributesName, const QStringList &atributesValue) = 0;
    virtual QString select() = 0;
//    virtual QString backUP(const QString &table) = 0;
};

#endif // IQUERYGENERATOR_H
