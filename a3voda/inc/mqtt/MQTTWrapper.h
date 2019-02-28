#ifndef MQTT_CLIENT_MQTT_WRAPPER_H
#define MQTT_CLIENT_MQTT_WRAPPER_H

#include <mosquittopp.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include <tools/KBDHelper.h>

#include <Poco/NotificationCenter.h>
#include <domain/ActionListener.h>

using namespace std;
using namespace Poco;

#define QOS 2

class MQTTWrapper : public mosqpp::mosquittopp {
public:
    MQTTWrapper(const char* id, const char* host, int port, vector<string> topics = {});
    virtual ~MQTTWrapper();
    void publish(string topic, string message);
    void publish(string topic, Serializable entity);
    void connect();
    void subscribeAction(ActionListener &listener);
private:
    vector<string> topics;
    NotificationCenter nc;
    void on_connect(int rc);
    void on_message(const struct mosquitto_message* message);
    string host;
    int port;
};

#endif //MQTT_CLIENT_MQTT_WRAPPER_H