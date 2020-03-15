#include <ThermostatManager.h>

using namespace thermostat;

ThermostatReadings ThermostatManager::getThermostatReadings(){
    TempAndHumidity tNh = tsens->getTempAndHumidity();
    if (isnan(tNh.humidity) || isnan(tNh.temperature)) {
        return this->currentValues;
    }
    this->currentValues.temperature = tNh.temperature;
    this->currentValues.humidity = tNh.humidity;
    this->currentValues.heatIndex = tsens->computeHeatIndex(tNh.temperature, tNh.humidity);
    return this->currentValues;
}

float ThermostatManager::getThreshold(){
    return _threshold;
}

void ThermostatManager::setThreshold(float t){
    if (isnan(t)) {
        return;
    }
    _threshold = t;
}

bool ThermostatManager::isEnabled() {
    return _enabled;
}

void ThermostatManager::enable() {
    _enabled = true;
}

void ThermostatManager::disable() {
    _enabled = false;
}