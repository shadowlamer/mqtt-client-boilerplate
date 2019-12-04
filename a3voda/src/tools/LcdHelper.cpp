/**
 * @file LcdHelper.cpp
 * @brief Реализация класса LcdHelper.
 * @author Vadim Cherenev
 * @date 21.02.2019
 * @copyright MIT License
 */

#include <LcdHelper.h>

/**
 * @brief Заменяет символы строки на заданный символ.
 * Например для ввода пароля
 * @param msg Исходная строка
 * @param mask Символ для замены
 * @return Строка с замененными символами
 */
string LcdHelper::mask(string msg, unsigned char mask) {
    string res="";
    for (unsigned int i=0;i<LCD_WIDTH;i++) {
        if (i<msg.size())
            if (mask!=0)
                res+=mask;
            else
                res+=msg[i];
        else
            res+=" ";
    }
    return res;
}
