#ifndef MQTT_CLIENT_BOILERPLATE_MQTTTASK_H
#define MQTT_CLIENT_BOILERPLATE_MQTTTASK_H

#include "Poco/Task.h"
#include "Poco/Process.h"
#include "Poco/TaskManager.h"
#include <Poco/Util/ServerApplication.h>

#include <mosquittopp.h>
#include <Server.h>
#include <MQTTWrapper.h>
#include <Main.h>
#include <MyPaymentSystem.h>

using namespace Poco;
using namespace std;
using namespace Poco::Util;

class MQTTTask: public Task {
public:
    MQTTTask();
    void runTask(void);
private:
    MQTTWrapper mqttWrapper;
    MyPaymentSystem paymentSystem;
};

#endif //MQTT_CLIENT_BOILERPLATE_MQTTTASK_H
