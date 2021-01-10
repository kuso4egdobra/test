#include "residencedoc.h"

ResidenceDoc::ResidenceDoc(int type_residence, QString region, int type_locality, QString name_locality,
                           QString street, int house, int building, int porch, int flat, int id_person,
                           datetime_t time_create, unsigned int version,unsigned int type_doc, unsigned int num_doc,
                           QString issuing_athority, datetime_t time_issuing, datetime_t time_start_action_doc,
                           datetime_t time_end_action_doc, fio_t fio, QVector<otherAtribute_t> &otherAtributes) :
    BaseDoc (id_person, time_create, version, type_doc, num_doc, issuing_athority, time_issuing, time_start_action_doc,
                 time_end_action_doc, fio, otherAtributes)
{
    this->type_residence = type_residence;
    this->region = region;
    this->type_locality = type_locality;
    this->name_locality = name_locality;
    this->street = street;
    this->house = house;
    this->building = building;
    this->porch = porch;
    this->flat = flat;
}
