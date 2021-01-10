#include "basedoc.h"

BaseDoc::BaseDoc(int id_person, datetime_t time_create, unsigned int version, unsigned int type_doc, unsigned int num_doc,
                 QString issuing_athority, datetime_t time_issuing, datetime_t time_start_action_doc,
                 datetime_t time_end_action_doc, fio_t fio, QVector<otherAtribute_t> &otherAtributes)
{
    this->id_person = id_person;
    this->time_create = time_create;
    this->version = version;
    this->type_doc = type_doc;
    this->num_doc = num_doc;
    this->issuing_athority = issuing_athority;
    this->time_issuing = time_issuing;
    this->time_start_action_doc = time_start_action_doc;
    this->time_end_action_doc = time_end_action_doc;
    this->fio = fio;
    this->otherAtributes = otherAtributes;
}

BaseDoc::BaseDoc()
{

}
