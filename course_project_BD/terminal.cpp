#include "terminal.h"

#include <QString>
#include <QTextStream>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

#include "BusinessLogic/DataToBusiness/datafromguitobusiness.h"
#include "BusinessLogic/businesslogic.h"

Terminal::Terminal()
{

}

void Terminal::run()
{
    QTextStream cin(stdin);
    QTextStream cout(stdout);
    DataFromGuiToBusiness sender;

    QString menu("\nChoose:\n"
                 "1. Enter file name\n"
                 "2. Get statistic\n"
                 "3. Exit\n"
                 "Enter: ");
    int choice = 0;
    bool cycle = true;
    while (cycle)
    {
        cout << menu;
        cout.flush();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            QString fileName;
            cout << "Enter file name: ";
            cout.flush();
            cin >> fileName;

            sender.setImport(fileName);
            break;
        }
        case 2:
        {
            QString menuStat;
            auto listName = sender.getListNameImport();
            for (int i = 0; i < listName.size(); i++)
            {
                menuStat += QString::number(i+1) + ". " + listName[i] + "\n";
            }
            menuStat += "Choose: ";
            cout << menuStat;
            cout.flush();
            cin >> choice;

            if (choice < 0 || choice > listName.size())
            {
                cout << "Error choice" << endl;
                break;
            }

            auto model = sender.sendSqlQuery(sender.getListSqlQueryImport()[choice - 1]);
            if (model)
            {
                QSqlQuery query = model->query();
                while (query.next())
                    qDebug() << query.record().value(0).toString();
            }
            else
                cout << "Error running sql query" << endl;

            break;
        }
        case 3:
        {
            cout << "Exiting application..." << endl;
            cycle = false;
            break;
        }
        default:
            cout << "Unknown num!" << endl;
        }
    }
}
