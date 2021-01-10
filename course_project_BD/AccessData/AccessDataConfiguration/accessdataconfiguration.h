#ifndef ACCESSDATACONFIGURATION_H
#define ACCESSDATACONFIGURATION_H

#include <QString>
#include "importinfoconnection.h"

class AccessDataConfiguration
{
    ImportInfoConnection *infoConnection;

public:
    AccessDataConfiguration();
    ~AccessDataConfiguration();
    ImportInfoConnection* getConfiguration();

};

#endif // ACCESSDATACONFIGURATION_H
