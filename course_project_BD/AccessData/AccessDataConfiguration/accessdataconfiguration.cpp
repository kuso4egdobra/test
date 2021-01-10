#include "accessdataconfiguration.h"

AccessDataConfiguration::AccessDataConfiguration()
{
    infoConnection = new ImportInfoConnection("/Users/kusok_dobra/course_project_BD/config.txt");
}

AccessDataConfiguration::~AccessDataConfiguration()
{
    delete infoConnection;
}

ImportInfoConnection *AccessDataConfiguration::getConfiguration()
{
    return infoConnection;
}
