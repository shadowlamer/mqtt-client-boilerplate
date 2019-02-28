//
// Created by sl on 21.02.2019.
//

#ifndef MQTT_CLIENT_LCDHELPER_H
#define MQTT_CLIENT_LCDHELPER_H

#include <string>

#define LCD_WIDTH 16

using namespace std;

class LcdHelper {
public:
   static string mask(string msg = "", unsigned char mask = 0);
};

#endif //MQTT_CLIENT_LCDHELPER_H
