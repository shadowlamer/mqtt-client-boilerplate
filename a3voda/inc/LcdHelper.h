/**
 * @file LcdHelper.h
 * @brief Заголовочный файл для класса LcdHelper.
 * @author Vadim Cherenev
 * @date 21.02.2019
 * @copyright MIT License
 */

#ifndef MQTT_CLIENT_LCDHELPER_H
#define MQTT_CLIENT_LCDHELPER_H

#include <string>

#define LCD_WIDTH 16

using namespace std;

/**
 * @class LcdHelper LcdHelper.h
 * @brief Содержит методы для упрощения вывода сообщений на LCD дисплей автомата.
 */

class LcdHelper {
public:
   static string mask(string msg = "", unsigned char mask = 0);
};

#endif //MQTT_CLIENT_LCDHELPER_H
