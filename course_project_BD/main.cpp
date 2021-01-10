#include "UI/mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <fstream>

#include "terminal.h"
#include "loggingcategories.h"

#define LOG_PATH "/Users/kusok_dobra/Desktop/logFile.txt"
#define DT_FORMAT "dd-MM-yyyy hh:mm:ss.zzz"

QScopedPointer<QFile> m_logFile;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void deleteOldData(QString fileName);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    deleteOldData(LOG_PATH);
    m_logFile.reset(new QFile(LOG_PATH));
    m_logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    qDebug(logInfo()) << "Запуск приложения...";

    MainWindow w;
    w.show();

    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(m_logFile.data());
    out << QDateTime::currentDateTime().toString(DT_FORMAT);

    switch (type)
    {
    case QtInfoMsg:     out << " INF "; break;
    case QtDebugMsg:    out << " DBG "; break;
    case QtWarningMsg:  out << " WRN "; break;
    case QtCriticalMsg: out << " CRT "; break;
    case QtFatalMsg:    out << " FTL "; break;
    }

    out << "*** " << context.category << ": " << msg << endl;
    out.flush();
}

void deleteOldData(QString fileName)
{
    try
    {
        QString res, tmp;
        QDateTime time;
        std::ifstream in(fileName.toStdString());
        QDateTime cur_minWeek(QDateTime::currentDateTime().addDays(-7));
        if (in.is_open())
        {
            std::string line, nameSqlQuery;
            while (getline(in, line))
            {
                tmp = line.data();
                tmp.resize(strlen(DT_FORMAT));
                time = QDateTime::fromString(tmp, DT_FORMAT);
                if (time >= cur_minWeek)
                {
                    res += line.data();
                    res += "\n";
                }
            }
            in.close();
        }
        std::ofstream out(fileName.toStdString());
        if (out.is_open())
        {
            out << res.toStdString();
            out.close();
        }
    }
    catch(...)
    {
        qDebug(logCritical()) << "Unable to open file in " << __FILE__;
    }
}
