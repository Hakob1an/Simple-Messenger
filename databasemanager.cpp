#include "databasemanager.h"

int DatabaseManager::_instanceCount = 0;

DatabaseManager::DatabaseManager()
{
    ++_instanceCount;
    _connectionName = QString("Connection%1").arg(_instanceCount);
    createConnection();
}

DatabaseManager::~DatabaseManager()
{
    _db.close();
    QSqlDatabase::removeDatabase(_connectionName);
}

bool DatabaseManager::createConnection()
{
    _db = QSqlDatabase::addDatabase("QSQLITE", _connectionName);
    _db.setDatabaseName("chat.db");

    if (!_db.open()) {
        qDebug() << "Cannot open database:" << _db.lastError().text();
        return false;
    }

    QSqlQuery query(_db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE, "
                    "password TEXT)")) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    // Create a new table for messages
    if (!query.exec("CREATE TABLE IF NOT EXISTS messages ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "sender TEXT, "
                    "recipient TEXT, "
                    "message TEXT, "
                    "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        qDebug() << "Failed to create messages table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::checkOrRegisterUser(const QString& username, const QString& password)
{
    QString hashedPassword = hashPassword(password);

    QSqlQuery query(_db);
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed to retrieve user:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toString() == hashedPassword;
    } else {
        return registerUser(username, hashedPassword);
    }
}

bool DatabaseManager::registerUser(const QString& username, const QString& password)
{
    QSqlQuery query(_db);
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to register user:" << query.lastError().text();
        return false;
    }

    return true;
}

QString DatabaseManager::hashPassword(const QString& password)
{
    QByteArray passwordBytes = password.toUtf8();

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        qDebug() << "Failed to create MD context";
        return QString();
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr)) {
        qDebug() << "Failed to initialize digest";
        EVP_MD_CTX_free(mdctx);
        return QString();
    }

    if (1 != EVP_DigestUpdate(mdctx, passwordBytes.constData(), passwordBytes.length())) {
        qDebug() << "Failed to update digest";
        EVP_MD_CTX_free(mdctx);
        return QString();
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &hashLen)) {
        qDebug() << "Failed to finalize digest";
        EVP_MD_CTX_free(mdctx);
        return QString();
    }

    EVP_MD_CTX_free(mdctx);

    QString hashedPassword;
    for (unsigned int i = 0; i < hashLen; ++i) {
        hashedPassword.append(QString("%1").arg(hash[i], 2, 16, QChar('0')));
    }

    return hashedPassword;
}

bool DatabaseManager::storeMessage(const QString& sender, const QString& recipient, const QString& message)
{
    QSqlQuery query(_db);
    query.prepare("INSERT INTO messages (sender, recipient, message) VALUES (:sender, :recipient, :message)");
    query.bindValue(":sender", sender);
    query.bindValue(":recipient", recipient);
    query.bindValue(":message", message);

    if (!query.exec()) {
        qDebug() << "Failed to store message:" << query.lastError().text();
        return false;
    }

    return true;
}

QList<ChatMessage> DatabaseManager::retrieveMessages()
{
    QList<ChatMessage> messages;

    QSqlQuery query("SELECT sender, recipient, message, timestamp FROM messages ORDER BY timestamp ASC", _db);

    while (query.next()) {
        ChatMessage chatMessage;
        chatMessage.sender = query.value(0).toString();
        chatMessage.recipient = query.value(1).toString();
        chatMessage.message = query.value(2).toString();
        chatMessage.timestamp = query.value(3).toDateTime();
        messages.append(chatMessage);
    }

    return messages;
}


