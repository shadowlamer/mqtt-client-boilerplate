//
// Created by sl on 21.02.2019.
//

#include <tools/LcdHelper.h>

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
