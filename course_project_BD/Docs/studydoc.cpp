#include "studydoc.h"

StudyDoc::StudyDoc(QString place, datetime_t time_start, datetime_t time_end, QString organization,
                   QString specialty, int id_person, datetime_t time_create, unsigned int version, unsigned int type_doc,
                   unsigned int num_doc, QString issuing_athority, datetime_t time_issuing,
                   datetime_t time_start_action_doc, datetime_t time_end_action_doc, fio_t fio,
                   QVector<otherAtribute_t> &otherAtributes) :
    BaseDoc (id_person, time_create, version, type_doc, num_doc, issuing_athority, time_issuing, time_start_action_doc,
             time_end_action_doc, fio, otherAtributes)

{
    this->place = place;
    this->time_start = time_start;
    this->time_end = time_end;
    this->organization = organization;
    this->specialty = specialty;
}
