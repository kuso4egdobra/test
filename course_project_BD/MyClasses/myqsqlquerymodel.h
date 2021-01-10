#ifndef MYQSQLQUERYMODEL_H
#define MYQSQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QVariant>
#include <QModelIndex>

class MyQSqlQueryModel : public QSqlQueryModel
{
    bool needToColorOldField;

public:
    MyQSqlQueryModel(bool needToColorOldField = false);
    MyQSqlQueryModel(QSqlQueryModel *model, bool needToColorOldField = false);

private:
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MYQSQLQUERYMODEL_H
