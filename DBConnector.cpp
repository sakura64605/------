#include "DBConnector.h"
#include <QDebug>

DBConnector::DBConnector() {}

bool DBConnector::connect(const QString &host, const QString &user, const QString &password, const QString &dbName) {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(password);
    db.setDatabaseName(dbName);
    db.setConnectOptions("MYSQL_OPT_RECONNECT=1");

    if (!db.open()) {
        qCritical() << "Database connection error:" << db.lastError().text();
        return false;
    }
    return true;
}

QSqlQuery DBConnector::executeQuery(const QString &query) {
    QSqlQuery q(db);
    if (!q.exec(query)) {
        qCritical() << "Query error:" << q.lastError().text() << "\nQuery:" << query;
    }
    return q;
}

void DBConnector::close() {
    if (db.isOpen()) {
        db.close();
        QSqlDatabase::removeDatabase(db.connectionName());
    }
}