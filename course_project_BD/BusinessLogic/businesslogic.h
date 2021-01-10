#ifndef BUSINESS_NEWDOC_H
#define BUSINESS_NEWDOC_H

#include <QString>

#include "doc_t.h"
#include "AccessData/AccessDataUtil/sqlaccessdatautil.h"
#include "ImportSqlQueries/importsqlqueries.h"

#include "Docs/birthdoc.h"
#include "Docs/deathdoc.h"
#include "Docs/marriagedoc.h"
#include "Docs/residencedoc.h"
#include "Docs/studydoc.h"
#include "Docs/workdoc.h"

class BusinessLogic
{
    SqlAccessDataUtil *access;
    ImportSqlQueries importSqlQueries;

public:
    BusinessLogic();
    BusinessLogic(SqlAccessDataUtil *access);
    ~BusinessLogic();

    virtual bool addNewDoc(BaseDoc &doc);
    virtual bool addNewDoc(BirthDoc &doc);
    virtual bool addNewDoc(DeathDoc &doc);
    virtual bool addNewDoc(MarriageDoc &doc);
    virtual bool addNewDoc(ResidenceDoc &doc);
    virtual bool addNewDoc(StudyDoc &doc);
    virtual bool addNewDoc(WorkDoc &doc);

    QSqlQueryModel* run(const QString &sqlString, bool needToLight);
//    void doBackUP();

    void setImport(QString fileName);
    QList<QPair<QString, QString>> getListImport();
    QList<QString> getListNameImport();
    QList<QString> getListSqlQueryImport();
    void setNeedToColorOldDocs(bool flag);

private:
    int checkId(int id);
    int updateDB(const QString &tableName, int idUpdate, const QStringList &atributesName, const QStringList &atributesValue);
    int insertDB(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue);
    void lightModel(QSqlQueryModel *model);

    void addNewDoc(BaseDoc &doc, int &id_person, int &id_doc);
    void addBaseDoc(BaseDoc &doc, int id_person, int &id_doc);
    int addFioForDoc(fio_t &fio, int id_person, int id_doc);
    int* addOtherAtributes(BaseDoc &doc, const int id_doc);
};

#endif // BUSINESS_NEWDOC_H
