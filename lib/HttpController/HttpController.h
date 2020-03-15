#ifndef HTTP_CONTROLLER_H
#define HTTP_CONTROLLER_H

#include <DNSServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ThermostatManager.h>

namespace http{

    class HttpController {
        protected:
            AsyncWebServer* _server = NULL;
            thermostat::ThermostatManager* _tMgr = NULL;

        public:
            HttpController(thermostat::ThermostatManager* mgr);
            void registerHandlers();

            ~HttpController();
    };

}

#endif