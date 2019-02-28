#ifndef MQTT_CLIENT_BOILERPLATE_SERVER_H
#define MQTT_CLIENT_BOILERPLATE_SERVER_H

#include <thread>
#include <unistd.h>
#include <fstream>
#include <Poco/Util/ServerApplication.h>
#include <MQTTTask.h>

using namespace Poco;
using namespace Poco::Util;
using namespace std;

class ServerApp : public ServerApplication
{
protected:
    int main(const vector<string> &);
};

#endif //MQTT_CLIENT_BOILERPLATE_SERVER_H
