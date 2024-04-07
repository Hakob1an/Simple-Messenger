#ifndef CRYPTO_H
#define CRYPTO_H

#include <QByteArray>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <QDebug>

class Crypto {
public:
    static QByteArray encrypt(const QByteArray &clearData, const QByteArray &key, const QByteArray &iv);
    static QByteArray decrypt(const QByteArray &encryptedData, const QByteArray &key, const QByteArray &iv);
};

#endif // CRYPTO_H
