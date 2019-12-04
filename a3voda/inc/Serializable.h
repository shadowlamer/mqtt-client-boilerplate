/**
 * @file Serializable.h
 * @brief Заголовочный файл для класса Serializable.
 * @author Vadim Cherenev
 * @date 13.02.2019
 * @copyright MIT License
 */

#ifndef MQTT_CLIENT_SERIALIZABLE_H
#define MQTT_CLIENT_SERIALIZABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <Poco/NotificationCenter.h>
#include <Poco/Notification.h>
#include <Poco/Observer.h>
#include <Poco/NObserver.h>
#include <Poco/AutoPtr.h>
#include <iostream>
using Poco::NotificationCenter;
using Poco::Notification;
using Poco::Observer;
using Poco::NObserver;
using Poco::AutoPtr;

using namespace std;
using namespace rapidjson;

/**
 * @brief Шаблон реализации геттера и сеттера для заданного поля.
 * @param TYPE Тип поля.
 * @param CLASS Имя текущего класса, для которого создаются методы.
 * @param GETTER Имя геттера.
 * @param SETTER Имя сеттера.
 * @param FIELD Имя связанного поля в JSON
 */
#define GETTER_SETTER(TYPE, CLASS, GETTER, SETTER, FIELD) \
TYPE CLASS::GETTER(TYPE d) const {return GetValue(FIELD,d);} \
void CLASS::SETTER(TYPE v) {AddMemberOrSetValue(FIELD, v);}

/**
 * @brief Шаблон заголовков геттера и сеттера для заданного поля.
 * @param TYPE Тип поля.
 * @param GETTER Имя геттера.
 * @param SETTER Имя сеттера.
 * @param VALUE Значение по-умолчанию.
 */
#define GETTER_SETTER_HEADER(TYPE, GETTER, SETTER, VALUE) \
TYPE GETTER(TYPE d = VALUE) const; \
void SETTER(TYPE value);

/**
 * @class Serializable Serializable.h
 * @brief Базовый класс для нагрузки MQTT сообщения.
 */
class Serializable : public rapidjson::Document, public Notification {
public:
    Serializable();
    Serializable(string json);
    Serializable(Serializable& other);
    void AddMemberOrSetValue(StringRefType, string value);
    void AddMemberOrSetValue(StringRefType, double value);
    void AddMemberOrSetValue(StringRefType, int value);
    const string GetValue(StringRefType, string defaultValue) const;
    double GetValue(StringRefType, double defaultValue) const;
    int GetValue(StringRefType, int defaultValue) const;
    void forceSetName(string name);
    string Serialize();
    string name() const override;

private:
    void AddMemberOrSetValue(StringRefType, Value value);
    string forcedName;
};

#endif //MQTT_CLIENT_SERIALIZABLE_H
