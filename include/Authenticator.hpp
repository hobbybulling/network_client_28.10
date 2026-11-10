#pragma once

#include <string>
#include <cstdint>

/**
 * \brief аутентификация клиента
 * 
 * генерируем соль, вычисляем хеш и формируем сообщение
 */
class Authenticator {
private:
    std::string saltHex;
    std::string passHash;
    std::string authMsg;

public:
    Authenticator() = default;

    /**
     * \brief генерируем случайную соль
     * \return строка из 16 шестнадцатеричных символов
     */
    std::string generateSalt();

    /**
     * \brief вычисляем хеш от переданной строки
     * \param inputData данные (соль + пароль)
     * \return хеш (шестнадцатеричная строка)
     */
    std::string calcSHA1(const std::string& inputData);

    /**
     * \brief формируем итоговое сообщение аутентификации
     * \param login логин
     * \param password пароль
     * \return строка формата LOGIN + SALT + HASH
     */
    std::string prepareAuthMsg(const std::string& login, const std::string& password);

    const std::string& getAuthMsg() const { return authMsg; }
};