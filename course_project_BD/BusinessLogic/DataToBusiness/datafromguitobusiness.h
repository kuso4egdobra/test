#ifndef DATAFROMGUITOBUSINESS_H
#define DATAFROMGUITOBUSINESS_H

#include "BusinessLogic/businesslogic.h"

#include <QDateTimeEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QTableWidget>

class DataFromGuiToBusiness
{
    BusinessLogic *business;
    bool needToDeleteBusiness;
public:
    DataFromGuiToBusiness();
    DataFromGuiToBusiness(BusinessLogic *business);
    ~DataFromGuiToBusiness();
    QSqlQueryModel* sendSqlQuery(QString &sqlString, bool needToLight = false);
    bool sendDataNewDoc(const QTableWidget *tableWidget,
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
                    const QComboBox *combo_resTypeLocality);

    void setImport(QString fileName);
    QList<QPair<QString, QString>> getListImport();
    QList<QString> getListNameImport();
    QList<QString> getListSqlQueryImport();
    void setFlagNeedToColorOldDocs(bool flag);
    void setBusinessLogic(BusinessLogic *busLogic);

private:
    datetime_t datetimeParser(QDateTime qdatetime);
    QString sexparser(int num);
    QVector<otherAtribute_t> otherAtributesParser(const QTableWidget *table);
};

#endif // DATAFROMGUITOBUSINESS_H
