#include "datafromguitobusiness.h"

#include <QDebug>

#include "loggingcategories.h"

DataFromGuiToBusiness::DataFromGuiToBusiness()
{
    needToDeleteBusiness = true;
    business = new BusinessLogic;
}

DataFromGuiToBusiness::DataFromGuiToBusiness(BusinessLogic *business)
{
    this->business = business;
    needToDeleteBusiness = false;
}

DataFromGuiToBusiness::~DataFromGuiToBusiness()
{
    if (needToDeleteBusiness)
        delete business;
}

QSqlQueryModel *DataFromGuiToBusiness::sendSqlQuery(QString &sqlString, bool needToLight)
{
    return business->run(sqlString, needToLight);
}

bool DataFromGuiToBusiness::sendDataNewDoc(const QTableWidget *tableWidget,
                                           const QLineEdit *lineEdit_patronymic,
                                           const QDateTimeEdit *time_start,
                                           const QLineEdit *lineEdit_name,
                                           const QCheckBox *checkBox_personInDB,
                                           const QDateTimeEdit *time_issuing,
                                           const QDateTimeEdit *time_create,
                                           const QComboBox *combo_sex,
                                           const QDateTimeEdit *time_end,
                                           const QSpinBox *spinBox_idPerson,
                                           const QLineEdit *lineEdit_authority,
                                           const QComboBox *combo_typeDoc,
                                           const QLineEdit *lineEdit_surname,
                                           const QSpinBox *spinBox_numDoc,
                                           const QSpinBox *spinBox_version,
                                           const QLineEdit *lineEdit_newTypeDoc,
                                           const QLineEdit *lineEdit_otherName,
                                           const QLineEdit *lineEdit_otherValue,
                                           const QComboBox *combo_sexPartner,
                                           const QLineEdit *lineEdit_partnerSurname,
                                           const QLineEdit *lineEdit_partnerPatronymic,
                                           const QDateTimeEdit *dateTimeEdit_marriageEnd,
                                           const QSpinBox *spinBox_idPartner,
                                           const QDateTimeEdit *dateTimeEdit_marriageStart,
                                           const QLineEdit *lineEdit_partnerName,
                                           const QLineEdit *lineEdit_workPlace,
                                           const QDateTimeEdit *dateTimeEdit_workStart,
                                           const QDateTimeEdit *dateTimeEdit_workEnd,
                                           const QLineEdit *lineEdit_workOrganization,
                                           const QLineEdit *lineEdit_workPosition,
                                           const QSpinBox *spinBox_workSalary,
                                           const QLineEdit *lineEdit_studyOrganization,
                                           const QLineEdit *lineEdit_studySpeciality,
                                           const QDateTimeEdit *dateTimeEdit_studyStart,
                                           const QLineEdit *lineEdit_studyPlace,
                                           const QDateTimeEdit *dateTimeEdit_studyEnd,
                                           const QLineEdit *lineEdit_birthPlace,
                                           const QDateTimeEdit *dateTimeEdit_birth,
                                           const QLineEdit *lineEdit_deathPlace,
                                           const QDateTimeEdit *dateTimeEdit_death,
                                           const QComboBox *combo_deathType,
                                           const QLineEdit *lineEdit_resRegion,
                                           const QLineEdit *lineEdit_resLocality,
                                           const QLineEdit *lineEdit_resStreet,
                                           const QSpinBox *spinBox_resHouse,
                                           const QSpinBox *spinBox_resBuilding,
                                           const QSpinBox *spinBox_resPorch,
                                           const QSpinBox *spinBox_resFlat,
                                           const QComboBox *combo_resType,
                                           const QComboBox *combo_resTypeLocality)
{
    bool res = 0;
    try
    {
        fio_t fio(lineEdit_surname->text(),
                  lineEdit_name->text(),
                  lineEdit_patronymic->text(),
                  sexparser(combo_sex->currentIndex()));
        QVector<otherAtribute_t> otherAtributes = otherAtributesParser(tableWidget);
        int id_person = checkBox_personInDB->isChecked() ? -1 : spinBox_idPerson->value();

        int type = combo_typeDoc->currentIndex();
        // при выборе "другого типа" документа вводится свой тип
        datetime_t dt_null;
        dt_null.null = true;
        switch (type)
        {
        case 0:
        {
            BaseDoc doc(id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                        uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                        datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                        otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        case 1:
        {
            BirthDoc doc(lineEdit_birthPlace->text(), datetimeParser(dateTimeEdit_birth->dateTime()),
                         id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                         uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                         datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                         otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        case 2:
        {
            DeathDoc doc(lineEdit_deathPlace->text(), datetimeParser(dateTimeEdit_death->dateTime()), combo_deathType->currentIndex(),
                         id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                         uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                         datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                         otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        case 3:
        {
            fio_t fioPartner(lineEdit_partnerSurname->text(),
                             lineEdit_partnerName->text(),
                             lineEdit_partnerPatronymic->text(),
                             sexparser(combo_sexPartner->currentIndex()));

            MarriageDoc doc(true, datetimeParser(dateTimeEdit_marriageStart->dateTime()), datetimeParser(dateTimeEdit_marriageEnd->dateTime()),
                            spinBox_idPartner->value(), fioPartner,
                            id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                            uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                            datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                            otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        case 4:
        {
            type--;
            fio_t fioPartner(lineEdit_partnerSurname->text(),
                             lineEdit_partnerName->text(),
                             lineEdit_partnerPatronymic->text(),
                             sexparser(combo_sexPartner->currentIndex()));

            MarriageDoc doc(false, datetimeParser(dateTimeEdit_marriageStart->dateTime()), datetimeParser(dateTimeEdit_marriageEnd->dateTime()),
                            spinBox_idPartner->value(), fioPartner,
                            id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                            uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                            datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                            otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        case 5:
        {
            type--;
            WorkDoc doc(lineEdit_workPlace->text(), datetimeParser(dateTimeEdit_workStart->dateTime()), datetimeParser(dateTimeEdit_workEnd->dateTime()),
                        lineEdit_workOrganization->text(), lineEdit_workPosition->text(), spinBox_workSalary->value(),
                        id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                        uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                        datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                        otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        case 6:
        {
            type--;
            StudyDoc doc(lineEdit_studyPlace->text(), datetimeParser(dateTimeEdit_studyStart->dateTime()), datetimeParser(dateTimeEdit_studyEnd->dateTime()),
                         lineEdit_studyOrganization->text(), lineEdit_studySpeciality->text(),
                         id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                         uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                         datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                         otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        case 7:
        {
            type--;
            ResidenceDoc doc(combo_resType->currentIndex(), lineEdit_resRegion->text(), combo_resTypeLocality->currentIndex(),
                             lineEdit_resLocality->text(), lineEdit_resStreet->text(), spinBox_resHouse->value(), spinBox_resBuilding->value(),
                             spinBox_resPorch->value(), spinBox_resFlat->value(),
                             id_person, datetimeParser(time_create->dateTime()), spinBox_version->value(),
                             uint (type), spinBox_numDoc->value(), lineEdit_authority->text(), datetimeParser(time_issuing->dateTime()),
                             datetimeParser(time_start->dateTime()), time_end ? datetimeParser(time_end->dateTime()) : dt_null, fio,
                             otherAtributes);
            res = business->addNewDoc(doc);
            break;
        }
        }
    }
    catch (...)
    {
        qDebug(logCritical()) << "Error in " << __FILE__;
    }

    return res;
}

void DataFromGuiToBusiness::setImport(QString fileName)
{
    business->setImport(fileName);
}

QList<QPair<QString, QString> > DataFromGuiToBusiness::getListImport()
{
    return business->getListImport();
}

QList<QString> DataFromGuiToBusiness::getListNameImport()
{
    return business->getListNameImport();
}

QList<QString> DataFromGuiToBusiness::getListSqlQueryImport()
{
    return business->getListSqlQueryImport();
}

void DataFromGuiToBusiness::setFlagNeedToColorOldDocs(bool flag)
{
    business->setNeedToColorOldDocs(flag);
}

void DataFromGuiToBusiness::setBusinessLogic(BusinessLogic *busLogic)
{
    delete business;
    business = busLogic;
}

datetime_t DataFromGuiToBusiness::datetimeParser(QDateTime qdatetime)
{
    datetime_t datetime;
    QDate qdate = qdatetime.date();
    QTime qTime = qdatetime.time();

    datetime.date = qdate.day();
    datetime.month = qdate.month();
    datetime.year = qdate.year();
    datetime.hour = qTime.hour();
    datetime.minute = qTime.minute();
    datetime.secs = qTime.second();
    datetime.time_need = true;

    return datetime;
}

QString DataFromGuiToBusiness::sexparser(int num)
{
    return num == 0 ? "M" : "F";
}

QVector<otherAtribute_t> DataFromGuiToBusiness::otherAtributesParser(const QTableWidget* table)
{
    QVector<otherAtribute_t> vector;
    for(int i = 0; i < table->rowCount(); i++)
    {
        auto name = table->item(i, 0)->text();
        auto value = table->item(i, 1)->text();

        vector.append(otherAtribute_t(name, value));
    }

    return vector;
}
