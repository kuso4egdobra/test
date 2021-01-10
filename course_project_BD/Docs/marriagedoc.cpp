#include "marriagedoc.h"

MarriageDoc::MarriageDoc(bool isStart, datetime_t time_start, datetime_t time_end, int id_partner,
                         fio_t fio_partner, int id_person, datetime_t time_create, unsigned int version, unsigned int type_doc,
                         unsigned int num_doc, QString issuing_athority, datetime_t time_issuing,
                         datetime_t time_start_action_doc, datetime_t time_end_action_doc, fio_t fio,
                         QVector<otherAtribute_t> &otherAtributes) :
    BaseDoc (id_person, time_create, version, type_doc, num_doc, issuing_athority, time_issuing, time_start_action_doc,
                 time_end_action_doc, fio, otherAtributes)
{
    this->isStart = isStart;
    this->time_start = time_start;
    this->time_end = time_end;
    this->id_partner = id_partner;
    this->fio_partner = fio_partner;
}
