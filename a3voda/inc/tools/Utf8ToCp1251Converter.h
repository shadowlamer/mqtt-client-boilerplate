//
// Created by sl on 27.02.2019.
//

#ifndef MQTT_CIVIL_CLIENT_UTF8TOCP1251CONVERTER_H
#define MQTT_CIVIL_CLIENT_UTF8TOCP1251CONVERTER_H

#include <iostream>
#include "Poco/UTF8Encoding.h"
#include <tools/Windows1251Encoding.h>
#include "Poco/TextConverter.h"

using namespace std;
using namespace Poco;

class Utf8ToCp1251Converter {
public:
    Utf8ToCp1251Converter();
    virtual ~Utf8ToCp1251Converter();
    static string cpToUtf(const string &source);
    static string utfToCp(const string &source);
};

#endif //MQTT_CIVIL_CLIENT_UTF8TOCP1251CONVERTER_H
