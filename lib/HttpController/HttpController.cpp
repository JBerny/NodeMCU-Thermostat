#include <HttpController.h>
#include <WebHandlers.h>

using namespace http;
using namespace thermostat;

HttpController::HttpController(ThermostatManager* mgr) {
    _server = new AsyncWebServer(80);
    _tMgr = mgr;
}

HttpController::~HttpController() {
    _server->end();
    delete _server;
}

void HttpController::registerHandlers(){
    Serial.println("Registering HTTP Handlers");
    ThermostatManager *mgr = this->_tMgr;
    _server->addHandler(new webhandlers::ReadingsWebHandler(mgr));
    _server->on("/temperature-control", HTTP_GET|HTTP_POST|HTTP_DELETE, [mgr](AsyncWebServerRequest *req){
        if (req->method() == HTTP_POST && req->hasParam("val")) {
            AsyncWebParameter *p = req->getParam("val");
            String val = p->value();
            Serial.println("Updating threshold "+val);
            mgr->setThreshold(std::atof(val.c_str()));
            Serial.println("Enabling temperature control");
            mgr->enable();
        } else if (req->method() == HTTP_DELETE) {
            Serial.println("Disabling temperature control");
            mgr->disable();
        }
        AsyncResponseStream *res = req->beginResponseStream("application/json");
        res->printf("{\"enabled\": %s, \"threshold\": %.2f }", 
                    mgr->isEnabled()?"true":"false", mgr->getThreshold() );
        req->send(res);
    });
    _server->onNotFound([](AsyncWebServerRequest *req){
        req->send(req->beginResponse(404));
    });
    _server->begin();
}