#ifndef DOC_T_H
#define DOC_T_H

#include <QStringList>
#include <QVector>
#include <QString>

const QStringList types({"birth", "death", "mariage", "work", "study", "residence"});

struct fio_t {
    QString surname;
    QString name;
    QString patronymic;
    QString sex;

    fio_t()
    {

    }

    fio_t(QString surname, QString name, QString patronymic, QString sex)
    {
        this->surname = surname;
        this->name = name;
        this->patronymic = patronymic;
        this->sex = sex;
    }
};

struct otherAtribute_t {
    QString name;
//    QString type;
    QString value;

    otherAtribute_t()
    {

    }

    otherAtribute_t(QString name, QString value)
    {
        this->name = name;
        this->value = value;
    }
};

struct datetime_t {
    int year;
    int month;
    int date;

    bool time_need;
    int hour;
    int minute;
    int secs;

    bool null = false;

    datetime_t()
    {

    }
};

struct doc_t {
    int id_person;
    datetime_t time_create;
    unsigned int version;

    unsigned int num_doc;
    char issuing_athority[300];
    datetime_t time_issuing;
    datetime_t time_start_action_doc;
    datetime_t time_end_action_doc;

    fio_t fio;
    unsigned int type_doc;

    union {
        struct {
            char place[200];
            datetime_t time_start;
            datetime_t time_end;
            char organization[100];
            char position[100];
            int salary;
        } work_t;

        struct {
            char place[200];
            datetime_t time_start;
            datetime_t time_end;
            char organization[100];
            char specialty[100];
        } study_t;

        struct {
            char place[200];
            datetime_t time;
        } birth_t;

        struct {
            char place[200];
            datetime_t time;
            unsigned int type_death;
        } death_t;

        struct {
            bool isStart;
            datetime_t time_start;
            datetime_t time_end;
            unsigned int id_partner; // если такого нет, то создать
            fio_t fio_partner; // так фио могло смениться
        } marriage_t;

        struct {
            int type_residence;
            char region[100];
            int type_locality;
            char name_locality[100];
            char street[100];
            int house;

            int building;
            int porch;
            int flat;
        } residence_t;

    } docs;

    QVector<otherAtribute_t> otherAtributes;
};


#endif // DOC_T_H
