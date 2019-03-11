
#ifndef MQTT_CLIENT_KBDHELPER_H
#define MQTT_CLIENT_KBDHELPER_H

#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/poll.h>
#include <map>

#define KBD_ENTER 'E'
#define KBD_BKSPACE 'B'
#define KBD_REGISTER 'R'

#define MAX_INPUT_SIZE 16

using namespace std;

class KBDHelper {
private:
    map <__u16 , char> keymap = {
            {82, '0'},
            {11, '0'},
            {79, '1'},
            {2,  '1'},
            {80, '2'},
            {3,  '2'},
            {81, '3'},
            {4,  '3'},
            {75, '4'},
            {5,  '4'},
            {76, '5'},
            {6,  '5'},
            {77, '6'},
            {7,  '6'},
            {71, '7'},
            {8,  '7'},
            {72, '8'},
            {9,  '8'},
            {73, '9'},
            {10, '9'},
            {13, '+'},
            {78, '+'},
            {12, '-'},
            {74, '-'},
            {55, KBD_REGISTER},      //Num section "*"
            {9+0x100, KBD_REGISTER}, //"8" with shift
            {96, KBD_ENTER},         //Num section "Enter"
            {4+0x100, KBD_ENTER},    //"3" with shift
            {115, KBD_ENTER},        //power key
            {14, KBD_BKSPACE}
    };
    string buf = "";
public:
    KBDHelper(string device);
    ~KBDHelper(void);
    string getDigit();
    string getBuf();
    bool inputString(string &str, unsigned int maxSize = MAX_INPUT_SIZE);
    bool checkSpecial(char special);
    void flush();

private:
    bool shift = false;
};

#endif //MQTT_CLIENT_KBDHELPER_H
