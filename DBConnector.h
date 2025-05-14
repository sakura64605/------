#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DBConnector {
public:
    DBConnector();
    bool connect(const QString &host, const QString &user, const QString &password, const QString &dbName);
    QSqlQuery executeQuery(const QString &query);
    void close();

private:
    QSqlDatabase db;
};

#endif // DBCONNECTOR_H