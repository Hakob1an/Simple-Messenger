#include "crypto.h"

QByteArray Crypto::encrypt(const QByteArray &clearData, const QByteArray &key, const QByteArray &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    QByteArray encryptedData;

    if (ctx) {
        encryptedData.resize(clearData.size() + AES_BLOCK_SIZE); // Allow space for padding
        int len = 0;
        int ciphertextLen = 0;

        // Initialize encryption operation
        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
            reinterpret_cast<const unsigned char*>(key.constData()),
            reinterpret_cast<const unsigned char*>(iv.constData()))) {

            // Provide the message to be encrypted
            if (EVP_EncryptUpdate(ctx,
                reinterpret_cast<unsigned char*>(encryptedData.data()), &len,
                reinterpret_cast<const unsigned char*>(clearData.constData()), clearData.size())) {
                ciphertextLen = len;

                // Finalize the encryption. Further ciphertext bytes may be written.
                if (EVP_EncryptFinal_ex(ctx,
                    reinterpret_cast<unsigned char*>(encryptedData.data()) + len, &len)) {
                    ciphertextLen += len;
                    encryptedData.resize(ciphertextLen); // Resize to final length
                }
            }
        }
        EVP_CIPHER_CTX_free(ctx); // Clean up
    }

    return encryptedData; // Return the encrypted data
}

QByteArray Crypto::decrypt(const QByteArray &encryptedData, const QByteArray &key, const QByteArray &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    QByteArray decryptedData;

    if (ctx) {
        decryptedData.resize(encryptedData.size());
        int len = 0;
        int plaintextLen = 0;

        // Initialize decryption operation
        if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
            reinterpret_cast<const unsigned char*>(key.constData()),
            reinterpret_cast<const unsigned char*>(iv.constData()))) {

            // Provide the message to be decrypted
            if (EVP_DecryptUpdate(ctx,
                reinterpret_cast<unsigned char*>(decryptedData.data()), &len,
                reinterpret_cast<const unsigned char*>(encryptedData.constData()), encryptedData.size())) {
                plaintextLen = len;

                // Finalize the decryption. Further plaintext bytes may be written.
                if (EVP_DecryptFinal_ex(ctx,
                    reinterpret_cast<unsigned char*>(decryptedData.data()) + len, &len)) {
                    plaintextLen += len;
                    decryptedData.resize(plaintextLen); // Resize to final length
                }
            }
        }
        EVP_CIPHER_CTX_free(ctx); // Clean up
    }

    return decryptedData; // Return the decrypted data
}
