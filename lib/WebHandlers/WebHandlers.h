#ifndef WEBHANDLERS_H
#define WEBHANDLERS_H

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ThermostatManager.h>

namespace webhandlers{

    class ReadingsWebHandler : public AsyncWebHandler {
        private:
            thermostat::ThermostatManager* _thermostatMgr;
            bool isMetrics(AsyncWebServerRequest *request);
            bool isReadings(AsyncWebServerRequest *request);

        public:
            ReadingsWebHandler(thermostat::ThermostatManager *manager);
            bool canHandle(AsyncWebServerRequest *request);
            void handleRequest(AsyncWebServerRequest *request);
            void handleReadingsRequest(AsyncWebServerRequest *request);
            void handleMetricsRequest(AsyncWebServerRequest *request);

    };

}

#endif