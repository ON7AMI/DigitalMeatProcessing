#include "commonobjects.h"


CommonObjects::CommonObjects()
{
}

bool CommonObjects::OpenDatabase()
{
    bool ok;
    QSqlDatabase mydb = QSqlDatabase::database();
    if (!mydb.isOpen())
    {
        QString m_sSettingsFile = QApplication::applicationDirPath() + "/appSettings.ini";
        QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
        QString hn, db, un, pw;
        hn = settings.value("HostName", "N/A").toString();
        db = settings.value("DatabaseName", "N/A").toString();
        un = settings.value("UserName", "N/A").toString();
        pw = settings.value("Password","N/A").toString();
        mydb = QSqlDatabase::addDatabase("QPSQL");
        mydb.setHostName(hn);
        mydb.setDatabaseName(db);
        mydb.setUserName(un);
        mydb.setPassword(pw);
        //bool heeft = mydb.driver()->hasFeature(QSqlDriver::LastInsertId);  // PostgreSQL heeft deze functie
        ok = mydb.open();
        qDebug() << "Has open the db: " << (ok ? "Yes" : "No") ;
    }
    else
    {
        qDebug() << "Database was open";
    }
    return ok;
}
