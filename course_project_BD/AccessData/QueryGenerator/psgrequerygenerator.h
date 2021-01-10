#ifndef PSGREQUERYGENERATOR_H
#define PSGREQUERYGENERATOR_H

#include "iquerygenerator.h"

class PsgreQueryGenerator : IQueryGenerator
{
public:
    PsgreQueryGenerator();
    QString insert(const QString &tableName, const QStringList &atributesName,
                   const QStringList &atributesValue) override;
    QString update(const QString &tableName, int idUpdate, const QStringList &atributesName,
                   const QStringList &atributesValue) override;
    QString select() override;
    QString getSamePeople(QString &tableName, int idPersonNotInclude,
                          QString &sameColumnName, QString &sameColumnValue);
//    QString backUP(const QString &table) override;
};

#endif // PSGREQUERYGENERATOR_H
