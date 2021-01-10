#include "deathdoc.h"

DeathDoc::DeathDoc(QString place, datetime_t time, unsigned int type_death, int id_person,
                   datetime_t time_create, unsigned int version, unsigned int type_doc, unsigned int num_doc,
                   QString issuing_athority, datetime_t time_issuing, datetime_t time_start_action_doc,
                   datetime_t time_end_action_doc, fio_t fio, QVector<otherAtribute_t> &otherAtributes) :
    BaseDoc (id_person, time_create, version, type_doc, num_doc, issuing_athority, time_issuing, time_start_action_doc,
                 time_end_action_doc, fio, otherAtributes)
{
    this->place = place;
    this->time = time;
    this->type_death = type_death;
}
