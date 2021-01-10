#include "businesslogic.h"

#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QColor>

#include "MyClasses/myqsqlquerymodel.h"
#include "loggingcategories.h"


QString timeparser(datetime_t dt)
{
    QString res;
    if (!dt.null)
    {
        res = QString(QString::number(dt.year)) + "-" +
                QString(QString::number(dt.month)) + "-" +
                QString(QString::number(dt.date));
        if (dt.time_need)
            res += " " + QString(QString::number(dt.hour)) + ":" +
                    QString(QString::number(dt.minute)) + ":" +
                    QString(QString::number(dt.secs));
    }
    else
        res = "NULL";

    return res;
}

void listparser(QStringList &lst)
{
    for (int i = 0; i < lst.size(); i++)
        if (lst[i] != "NULL")
            lst[i] = "'" + lst[i] + "'";
}

// возможно нужно будет переделать
QStringList mariageparser(MarriageDoc &doc)
{
    QStringList res("NULL");
    if (doc.isStart)
        res.push_front(QString(timeparser(doc.time_start)));
    else
        res.push_back(QString(timeparser(doc.time_end)));

    return res;
}

void residenceparser(QStringList &list, int num)
{
    if (num > 0)
        list.append(QString(QString::number(num)));
    else
        list.append("NULL");
}

BusinessLogic::BusinessLogic()
{
    access = new SqlAccessDataUtil();
}

BusinessLogic::BusinessLogic(SqlAccessDataUtil *access)
{
    this->access = access;
}

BusinessLogic::~BusinessLogic()
{
    delete access;
}

int BusinessLogic::addFioForDoc(fio_t &fio, int id_person, int id_doc)
{
    int id_fio = -1;
    if (fio.name.size() > 0)
    {
        QStringList fioList({QString(QString::number(id_doc)),
                         QString(fio.surname),
                         QString(fio.name),
                         QString(fio.patronymic),
                         QString(fio.sex)});
        listparser(fioList);

        id_fio = insertDB("fio", QStringList({"id_doc", "surname", "name", "patronymic", "sex"}), fioList);
        if (id_fio < 0)
            throw "Unable to create record in table fio";

        updateDB("person", id_person, QStringList({"id_fio"}), QStringList({QString::number(id_fio)}));
    }

    return id_fio;
}

int* BusinessLogic::addOtherAtributes(BaseDoc &doc, const int id_doc)
{
    // проверить при нулевой длине, будет ли NULL
    int *resMas = new int [doc.otherAtributes.size()];
    for(int i = 0; i < doc.otherAtributes.size() && resMas; i++)
    {
        QStringList lst({QString(QString::number(id_doc)),
                         doc.otherAtributes[i].name,
                         doc.otherAtributes[i].value});
        listparser(lst);

        int id_otherAtribute = insertDB("other_atribute", QStringList({"id_doc", "name", "value"}), lst);
        if (id_otherAtribute < 0)
        {
            delete[] resMas;
            resMas = nullptr;
            throw "Unable to create record in table other_atribute";
        }
        else
         resMas[i] = id_otherAtribute;
    }

    return resMas;
}

void BusinessLogic::addBaseDoc(BaseDoc &doc, int id_person, int &id_doc)
{
    // !! везде нужно обновить отношения
    //! попробовать сделать откат с помощью rollback
    // добавить проверку по совпадению кол-ву аргументов у двух QStringList
    // тут некоторых переменных связанные со временем может не быть
    // посмотреть как сделать откат при выполнении только части операций
    QStringList lst({timeparser(doc.time_create),
                     QString(QString::number(doc.version)),
                     QString(QString::number(doc.type_doc)),
                     QString(QString::number(doc.num_doc)),
                     QString(doc.issuing_athority),
                     timeparser(doc.time_issuing),
                     timeparser(doc.time_start_action_doc),
                     timeparser(doc.time_end_action_doc),
                     QString(QString::number(id_person))});
    listparser(lst);

    id_doc = insertDB("document", QStringList({"time_create", "version", "type_doc", "num_doc", "issuing_athority", "time_issuing",
                                          "time_start_action_doc", "time_end_action_doc", "id_person"}), lst);
    if (id_doc < 0)
        throw "Unable to create record in table document";

    addFioForDoc(doc.fio, id_person, id_doc);

    int *ids_otherAtributes = addOtherAtributes(doc, id_doc);
    delete[] ids_otherAtributes;
}

void BusinessLogic::addNewDoc(BaseDoc& doc, int &id_person, int &id_doc)
{
    id_person = checkId(doc.id_person);
    if (id_person < 0)
        throw "Error in searching/creating human in table person";

    addBaseDoc(doc, id_person, id_doc);
}

bool BusinessLogic::addNewDoc(BaseDoc &doc)
{
    qDebug(logInfo()) << "Adding BaseDoc to DB...";
    bool res = true;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        int id_person, id_doc;
        addNewDoc(doc, id_person, id_doc);

        if (!access->commit())
            throw "Unable to commit transaction";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in adding new BaseDoc";
        access->rollback();
        res = false;
    }

    return res;
}

bool BusinessLogic::addNewDoc(BirthDoc &doc)
{
    qDebug(logInfo()) << "Adding BirthDoc to DB...";
    bool res = true;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        int id_person, id_doc;
        addNewDoc(doc, id_person, id_doc);

        QStringList birth({QString(QString::number(id_doc)),
                           QString(doc.place),
                           timeparser(doc.time)});
        listparser(birth);

        int id_birth = insertDB("birth", QStringList({"id_doc", "place", "time"}), birth);
        if (id_birth < 0)
            throw "Unable to create record in table birth";

        updateDB("person", id_person, QStringList({"id_birth"}), QStringList({QString(QString::number(id_birth))}));

        if (!access->commit())
            throw "Unable to commit transaction";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in adding new BirthDoc";
        access->rollback();
        res = false;
    }

    return res;
}

bool BusinessLogic::addNewDoc(DeathDoc &doc)
{
    qDebug(logInfo()) << "Adding DeathDoc to DB...";
    bool res = true;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        int id_person, id_doc;
        addNewDoc(doc, id_person, id_doc);

        QStringList death({QString(QString::number(id_doc)),
                           QString(doc.place),
                           timeparser(doc.time),
                           QString(QString::number(doc.type_death))});
        listparser(death);

        int id_death = insertDB("death", QStringList({"id_doc", "place", "time", "type_death"}), death);
        if (id_death < 0)
            throw "Unable to create record in table death";

        updateDB("person", id_person, QStringList({"id_death"}), QStringList({QString(QString::number(id_death))}));

        if (!access->commit())
            throw "Unable to commit transaction";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in adding new DeathDoc";
        access->rollback();
        res = false;
    }

    return res;
}

bool BusinessLogic::addNewDoc(MarriageDoc &doc)
{
    qDebug(logInfo()) << "Adding MarriageDoc to DB...";
    bool res = true;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        int id_person, id_doc;
        addNewDoc(doc, id_person, id_doc);

        // что делать с браком, если приходит инфа только о заключении/расторжении
        int id_partner_doc, id_partner = doc.id_partner;
        doc.fio = doc.fio_partner;
        doc.id_person = doc.id_partner;
        addNewDoc(doc, id_partner, id_partner_doc);
        if (id_partner <= 0)
            throw "Unable to create partner person";


        QStringList mariageTime = mariageparser(doc);
        QStringList mariage({QString(QString::number(id_doc)),
                             mariageTime[0],
                             mariageTime[1],
                             QString(QString::number(id_partner))});
        listparser(mariage);

        if (insertDB("marriage", QStringList({"id_doc", "time_start", "time_end", "id_partner"}), mariage) < 0)
            throw "Unable to create record in table marriage";

        QStringList mariage2({QString(QString::number(id_partner_doc)),
                               mariageTime[0],
                               mariageTime[1],
                               QString(QString::number(id_person))});
        listparser(mariage2);

        if (insertDB("marriage", QStringList({"id_doc", "time_start", "time_end", "id_partner"}), mariage2) < 0)
            throw "Unable to create record in table marriage for partner";

        QStringList relation({QString(QString::number(id_doc)),
                              QString(QString::number(id_person)),
                              QString(QString::number(id_partner)),
                              QString(QString::number(0))});
        listparser(relation);

        if (insertDB("relations", QStringList({"id_doc", "id_person1", "id_person2", "type_relations"}), relation) < 0)
            throw "Unable to create relation";

        if (!access->commit())
            throw "Unable to commit transaction";

    }
    catch(QString str)
    {
        qDebug(logCritical()) << str;
        qDebug(logCritical()) << "Error in adding new MarriageDoc";
        access->rollback();
        res = false;
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in adding new MarriageDoc";
        access->rollback();
        res = false;
    }

    return res;
}

bool BusinessLogic::addNewDoc(ResidenceDoc &doc)
{
    qDebug(logInfo()) << "Adding ResidenceDoc to DB...";
    bool res = true;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        int id_person, id_doc;
        addNewDoc(doc, id_person, id_doc);

        QStringList residence({QString(QString::number(id_doc)),
                               QString(QString::number(doc.type_residence)),
                               QString(doc.region),
                               QString(QString::number(doc.type_locality)),
                               QString(doc.name_locality),
                               QString(doc.street),
                               QString(QString::number(doc.house))});

        residenceparser(residence, doc.building);
        residenceparser(residence, doc.porch);
        residenceparser(residence, doc.flat);

        listparser(residence);

        if (insertDB("residence", QStringList({"id_doc", "type_residence", "region", "type_locality", "name_locality",
                                              "street", "house", "building", "porch", "flat"}), residence) < 0)
            throw "Unable to create record in table residence";

        if (!access->commit())
            throw "Unable to commit transaction";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in adding new ResidenceDoc";
        access->rollback();
        res = false;
    }

    return res;
}

bool BusinessLogic::addNewDoc(StudyDoc &doc)
{
    qDebug(logInfo()) << "Adding StudyDoc to DB...";
    bool res = true;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        int id_person, id_doc;
        addNewDoc(doc, id_person, id_doc);

        QStringList study({QString(QString::number(id_doc)),
                           QString(doc.place),
                           timeparser(doc.time_start),
                           timeparser(doc.time_end),
                           QString(doc.organization),
                           QString(doc.specialty)});
        listparser(study);

        if (insertDB("study", QStringList({"id_doc", "place", "time_start", "time_end", "organization", "specialty"}), study) < 0)
            throw "Unable to create record in table study";

        QStringList listIdStudents = access->getSamePeople("study", id_person, "organization", doc.organization);
        for (int i = 0; i < listIdStudents.size(); i++)
        {
            QStringList relation({QString(QString::number(id_doc)),
                                  QString(QString::number(id_person)),
                                  QString(listIdStudents[i]),
                                  QString(QString::number(1))});
            listparser(relation);

            if (insertDB("relations", QStringList({"id_doc", "id_person1", "id_person2", "type_relations"}), relation) < 0)
                throw "Unable to create relation";
        }

        if (!access->commit())
            throw "Unable to commit transaction";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in adding new StudyDoc";
        access->rollback();
        res = false;
    }

    return res;
}

bool BusinessLogic::addNewDoc(WorkDoc &doc)
{
    qDebug(logInfo()) << "Adding WorkDoc to DB...";
    bool res = true;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        int id_person, id_doc;
        addNewDoc(doc, id_person, id_doc);

        QStringList work({QString(QString::number(id_doc)),
                          QString(doc.place),
                          timeparser(doc.time_start),
                          timeparser(doc.time_end),
                          QString(doc.organization),
                          QString(doc.position),
                          QString(QString::number(doc.salary))});
        listparser(work);

        if (insertDB("work", QStringList({"id_doc", "place", "time_start", "time_end",
                                         "organization", "position", "salary"}), work) < 0)
            throw "Unable to create record in table work";

        QStringList listIdWorkers = access->getSamePeople("work", id_person, "organization", doc.organization);
        for (int i = 0; i < listIdWorkers.size(); i++)
        {
            QStringList relation({QString(QString::number(id_doc)),
                                  QString(QString::number(id_person)),
                                  QString(listIdWorkers[i]),
                                  QString(QString::number(2))});
            listparser(relation);

            if (insertDB("relations", QStringList({"id_doc", "id_person1", "id_person2", "type_relations"}), relation) < 0)
                throw "Unable to create relation";
        }

        if (!access->commit())
            throw "Unable to commit transaction";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in adding new WorkDoc";
        access->rollback();
        res = false;
    }

    return res;
}

QSqlQueryModel *BusinessLogic::run(const QString &sqlString, bool needToLight)
{
    qDebug(logInfo()) << "Running SQL-Query";
    MyQSqlQueryModel* model = nullptr;
    try
    {
        if (!access->transaction())
            throw "Unable to start transaction";

        model = access->run(sqlString);

        if (!access->commit())
            throw "Unable to commit transaction";

        if (needToLight)
        {
            lightModel(model);
        }
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in running admin";
        access->rollback();

        if (model)
            delete model;
        model = nullptr;
    }

    return model;
}

//void Business_NewDoc::doBackUP()
//{
//    access->doBackUP();
//}

void BusinessLogic::setImport(QString fileName)
{
    importSqlQueries.setConfigFile(fileName);
}

QList<QPair<QString, QString> > BusinessLogic::getListImport()
{
    return importSqlQueries.getList();
}

QList<QString> BusinessLogic::getListNameImport()
{
    return importSqlQueries.getListName();
}

QList<QString> BusinessLogic::getListSqlQueryImport()
{
    return importSqlQueries.getListSqlQuery();
}

void BusinessLogic::setNeedToColorOldDocs(bool flag)
{
    access->setFlagNeedToColorOldDocs(flag);
}

int BusinessLogic::checkId(int id)
{
    if (id > 0) // проверка существования id_person
        // добавить проверку на существование в БД
        return id;

    id = insertDB("person", QStringList({"id_fio", "id_birth", "id_death"}), QStringList({"NULL", "NULL", "NULL"}));

    return id;
}

int BusinessLogic::updateDB(const QString &tableName, int idUpdate, const QStringList &atributesName, const QStringList &atributesValue)
{
    if (atributesName.size() != atributesValue.size())
        throw "Invalid size of lists when updating";

    if (idUpdate < 0)
        throw "Invalid id to update";

    return access->update(tableName, idUpdate, atributesName, atributesValue);
}

int BusinessLogic::insertDB(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue)
{
    if (atributesName.size() != atributesValue.size())
        throw "Invalid size of lists when inserting";

    return access->insert(tableName, atributesName, atributesValue);
}

void BusinessLogic::lightModel(QSqlQueryModel *model)
{
//    model = new MyQSqlQueryModel(model);
//    auto query = model->query();
//    while (query.next())
//    {
////        qDebug() << query.record();
//        for (int i = 0; i < query.size(); i++)
//        {
//            qDebug() << query.record().field(i).name();
//            if (query.record().field(i).name() == "time_issuing")
//                model->setData(QModelIndex(), QColor(Qt::green));
//        }
//    }



}
