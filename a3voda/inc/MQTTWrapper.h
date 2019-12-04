/**
 * @file MQTTWrapper.h
 * @brief Заголовочный файл для класса MQTTWrapper.
 * @author Vadim Cherenev
 * @date 21.02.2019
 * @copyright MIT License
 */

#ifndef MQTT_CLIENT_MQTT_WRAPPER_H
#define MQTT_CLIENT_MQTT_WRAPPER_H

#include <mosquittopp.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include <KBDHelper.h>

#include <Poco/NotificationCenter.h>
#include <ActionListener.h>

using namespace std;
using namespace Poco;

/**
 * @brief QOS для отправки сообщений.
 * 0 - доставка не гарантируется
 * 1 - сообщение будет доставлено минимум один раз
 * 2 - сообение будет доставлено ровно один раз
 */
#define QOS 2

/**
 * @class MQTTWrapper MQTTWrapper.h
 * @brief Содержит методы для отправки и получения MQTT сообщений.
 */
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