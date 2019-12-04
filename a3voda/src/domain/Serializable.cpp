/**
 * @file Serializable.cpp
 * @brief Реализация класса Serializable.
 * @author Vadim Cherenev
 * @date 13.02.2019
 * @copyright MIT License
 */

#include <Serializable.h>
#include <iostream>

/**
 * Создает сообщение из строки JSON
 * @param json Строка JSON
 */
Serializable::Serializable(string json) : Document() {
    Parse(json.c_str());
}

Serializable::Serializable() : Document() {
    SetObject();
};

/**
 * Копирующий конструктор
 * @param other Другой экземпляр Serializable
 */
Serializable::Serializable(Serializable &other) : Serializable(other.Serialize()) {}

/**
 * @brief Добавляет полe, или задает значение существующего.
 * @param name Имя поля.
 * @param value Значение поля.
 */
void Serializable::AddMemberOrSetValue(StringRefType name, Value value) {
    RemoveMember(name);
    AddMember(name, value, GetAllocator());
}

/**
 * @brief Добавляет полe, или задает значение существующего.
 * @param name Имя поля.
 * @param value Значение поля.
 */
void Serializable::AddMemberOrSetValue(StringRefType name, string value) {
    AddMemberOrSetValue(name, Value(value.c_str(), GetAllocator()));
}

/**
 * @brief Добавляет полe, или задает значение существующего.
 * @param name Имя поля.
 * @param value Значение поля.
 */
void Serializable::AddMemberOrSetValue(StringRefType name, double value) {
    AddMemberOrSetValue(name, Value(value));
}

/**
 * @brief Добавляет полe, или задает значение существующего.
 * @param name Имя поля.
 * @param value Значение поля.
 */
void Serializable::AddMemberOrSetValue(StringRefType name, int value) {
    AddMemberOrSetValue(name, Value(value));
}

/**
 * @brief Получает текущее значение поля
 * @param name Имя поля.
 * @param defaultValue Значение поля по-умолчанию.
 * @return Текущее значение поля или defaultValue, если такого поля не существует.
 */
const string Serializable::GetValue(StringRefType name, string defaultValue) const {
    return HasMember(name)?(*this)[name.s].GetString():defaultValue;
}

/**
 * @brief Получает текущее значение поля
 * @param name Имя поля.
 * @param defaultValue Значение поля по-умолчанию.
 * @return Текущее значение поля или defaultValue, если такого поля не существует.
 */
double Serializable::GetValue(StringRefType name, double defaultValue) const {
    return HasMember(name)?(*this)[name.s].GetDouble():defaultValue;
}

/**
 * @brief Получает текущее значение поля
 * @param name Имя поля.
 * @param defaultValue Значение поля по-умолчанию.
 * @return Текущее значение поля или defaultValue, если такого поля не существует.
 */
int Serializable::GetValue(StringRefType name, int defaultValue) const {
    return HasMember(name)?(*this)[name.s].GetInt():defaultValue;
}

/**
 * @brief Сериализует экземпляр класса в строку JSON
 * @return строка JSON
 */
string Serializable::Serialize() {
    StringBuffer s;
    s.Clear();
    Writer<StringBuffer> writer(s);
    Serializable::Accept(writer);
    return s.GetString();
}

/**
 * @brief Задает имя для сообщения.
 * Имя - дополнительное поле в котором можно передать информацию.
 * Например об источнике сообщения.
 * @param name Новое имя сообщения.
 */
void Serializable::forceSetName(string name) {
    forcedName = move(name);
}

/**
 * @return Имя сообщения.
 */
string Serializable::name() const {
    if (!forcedName.empty())
        return forcedName;
    return Notification::name();
}

