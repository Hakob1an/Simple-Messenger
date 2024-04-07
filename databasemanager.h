#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <openssl/evp.h>
#include <QList>
#include <QDateTime>

struct ChatMessage {
    QString sender;
    QString recipient;
    QString message;
    QDateTime timestamp; // Assuming you might also want to display or use the timestamp
};

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    bool createConnection();
    bool checkOrRegisterUser(const QString& username, const QString& password);
    bool storeMessage(const QString& sender, const QString& recipient, const QString& message);
    QList<ChatMessage> retrieveMessages();

private:
    QSqlDatabase _db;
    static int _instanceCount;
    QString _connectionName;

    QString hashPassword(const QString& password);
    bool registerUser(const QString& username, const QString& password);
};

#endif // DATABASEMANAGER_H
