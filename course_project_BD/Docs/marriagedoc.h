#ifndef MARRIAGEDOC_H
#define MARRIAGEDOC_H

#include "basedoc.h"

class MarriageDoc : public BaseDoc
{
public:
    bool isStart;
    datetime_t time_start;
    datetime_t time_end;
    int id_partner; // если такого нет, то создать
    fio_t fio_partner; // так фио могло смениться

public:
    MarriageDoc(bool isStart, datetime_t time_start, datetime_t time_end, int id_partner, fio_t fio_partner,
                int id_person, datetime_t time_create, unsigned int version, unsigned int type_doc, unsigned int num_doc,
                QString issuing_athority, datetime_t time_issuing, datetime_t time_start_action_doc,
                datetime_t time_end_action_doc, fio_t fio, QVector<otherAtribute_t> &otherAtributes);
};

#endif // MARRIAGEDOC_H
