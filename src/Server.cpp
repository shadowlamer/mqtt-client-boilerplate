#include <Server.h>

int ServerApp::main(const vector<string> &)
{
    TaskManager tm;
    cerr << "Server started" << endl;
    try {
        tm.start(new MQTTTask());
    } catch (int e) {
        cerr << e << endl;
    }
    waitForTerminationRequest();
    tm.cancelAll();
    tm.joinAll();

    return Application::EXIT_OK;
}
