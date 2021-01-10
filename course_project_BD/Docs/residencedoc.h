#ifndef RESIDENCEDOC_H
#define RESIDENCEDOC_H

#include "basedoc.h"

class ResidenceDoc : public BaseDoc
{
public:
    int type_residence;
    QString region;
    int type_locality;
    QString name_locality;
    QString street;
    int house;

    int building;
    int porch; // подъезд
    int flat;

public:
    ResidenceDoc(int type_residence, QString region, int type_locality, QString name_locality, QString street,
                 int house, int building, int porch, int flat, int id_person, datetime_t time_create,
                 unsigned int version, unsigned int type_doc, unsigned int num_doc, QString issuing_athority,
                 datetime_t time_issuing, datetime_t time_start_action_doc,
                 datetime_t time_end_action_doc, fio_t fio, QVector<otherAtribute_t> &otherAtributes);
};

#endif // RESIDENCEDOC_H
