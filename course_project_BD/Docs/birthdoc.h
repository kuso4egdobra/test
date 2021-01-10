#ifndef BIRTHDOC_H
#define BIRTHDOC_H

#include "basedoc.h"

class BirthDoc : public BaseDoc
{
public:
    QString place;
    datetime_t time;
public:
    BirthDoc(QString place, datetime_t time, int id_person, datetime_t time_create, unsigned int version, unsigned int type_doc,
             unsigned int num_doc, QString issuing_athority, datetime_t time_issuing, datetime_t time_start_action_doc,
             datetime_t time_end_action_doc, fio_t fio, QVector<otherAtribute_t> &otherAtributes);
};

#endif // BIRTHDOC_H
