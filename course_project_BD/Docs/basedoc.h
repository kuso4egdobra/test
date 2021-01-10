#ifndef BASEDOC_H
#define BASEDOC_H

#include <QString>
#include <QVector>

#include "doc_t.h"

class BaseDoc
{
public:
    int id_person;
    datetime_t time_create;
    unsigned int version;
    unsigned int type_doc;

    unsigned int num_doc;
    QString issuing_athority;
    datetime_t time_issuing;
    datetime_t time_start_action_doc;
    datetime_t time_end_action_doc;

    fio_t fio;

    QVector<otherAtribute_t> otherAtributes;

public:
    BaseDoc(int id_person, datetime_t time_create, unsigned int version, unsigned int type_doc, unsigned int num_doc,
            QString issuing_athority, datetime_t time_issuing, datetime_t time_start_action_doc,
            datetime_t time_end_action_doc, fio_t fio, QVector<otherAtribute_t> &otherAtributes);
    BaseDoc();

};

#endif // BASEDOC_H
