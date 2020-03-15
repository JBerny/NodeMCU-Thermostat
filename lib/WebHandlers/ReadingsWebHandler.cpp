#include <WebHandlers.h>

using namespace webhandlers;

ReadingsWebHandler::ReadingsWebHandler(thermostat::ThermostatManager *manager) {
    _thermostatMgr = manager;
}

bool ReadingsWebHandler::canHandle(AsyncWebServerRequest *request) {
    return isReadings(request) || isMetrics(request);
}

bool ReadingsWebHandler::isMetrics(AsyncWebServerRequest *request) {
    return request->url().equals("/metrics");
}

bool ReadingsWebHandler::isReadings(AsyncWebServerRequest *request) {
    return request->url().equals("/readings");
}

void ReadingsWebHandler::handleRequest(AsyncWebServerRequest *request) {
    if (isReadings(request)){
        Serial.println("ThermostatWebHandler::handleReadingsRequest");
        handleReadingsRequest(request);
    } else {
        Serial.println("ThermostatWebHandler::handleReadingsRequest");
        handleMetricsRequest(request);
    }
}

void ReadingsWebHandler::handleReadingsRequest(AsyncWebServerRequest *request) {   
    AsyncResponseStream* resp = request->beginResponseStream("application/json");
    resp->setCode(200);
    thermostat::ThermostatReadings reads = this->_thermostatMgr->getThermostatReadings();
    resp->printf("{\"temperature\":%.2f,\"humidity\":%.2f,\"heatIndex\":%.2f}",
                reads.temperature, reads.humidity, reads.heatIndex);
    request->send(resp);
};

void ReadingsWebHandler::handleMetricsRequest(AsyncWebServerRequest *request) {   
    AsyncResponseStream* resp = request->beginResponseStream("application/json");
    resp->setCode(200);
    thermostat::ThermostatReadings reads = this->_thermostatMgr->getThermostatReadings();
    resp->printf("# HELP sensor_heat_index calculated value of the apparent temperature\n");
    resp->printf("# TYPE sensor_heat_index gauge\n");
    resp->printf("sensor_heat_index %f\n", reads.heatIndex);
    resp->printf("# HELP sensor_humidity humidity percentage read from DHT11\n");
    resp->printf("# TYPE sensor_humidity gauge\n");
    resp->printf("sensor_humidity %f\n", reads.humidity);
    resp->printf("# HELP sensor_temperature temperature value read from DHT11\n");
    resp->printf("# TYPE sensor_temperature gauge\n");
    resp->printf("sensor_temperature %f\n", reads.temperature);
    request->send(resp);
};

void Temperature(thermostat::ThermostatManager *mgr, AsyncWebServerRequest *req) {
    AsyncResponseStream* resp = req->beginResponseStream("application/json");
    resp->setCode(200);
    Serial.println("ThermostatWebHandler::handleRequest");
    thermostat::ThermostatReadings reads = mgr->getThermostatReadings();
    resp->printf("{\"temperature\":%.2f,\"humidity\":%.2f,\"heatIndex\":%.2f}",
                reads.temperature, reads.humidity, reads.heatIndex);
    req->send(resp);
}

