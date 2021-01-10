
#include "myqsqlquerymodel.h"

#include <QColor>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include <QDateTime>

MyQSqlQueryModel::MyQSqlQueryModel(bool needToColorOldField) : QSqlQueryModel ()
{
    this->needToColorOldField = needToColorOldField;
}


MyQSqlQueryModel::MyQSqlQueryModel(QSqlQueryModel *model, bool needToColorOldField) : QSqlQueryModel (model)
{
    this->needToColorOldField = needToColorOldField;
}

QVariant MyQSqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant res;
    if (role == Qt::TextColorRole)
    {
        auto rec = record(index.row());
        if (needToColorOldField
                && rec.field("time_end_action_doc").value().toDateTime() < QDateTime::currentDateTime()
                && rec.field("time_end_action_doc").value().toDateTime().isValid())
            res = QVariant(QColor(Qt::red));
        else
            res = QSqlQueryModel::data(index, role);
    }
    else
        res = QSqlQueryModel::data(index, role);

    return res;
}

