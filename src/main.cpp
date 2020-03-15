#include <Arduino.h>
#include <Secrets.h>
#include <WiFiManager.h>
#include <UI.h>
#include <DHTesp.h>
#include <ThermostatManager.h>
#include <HttpController.h>

// Init WiFi connection
WiFiManager wifiman(SSID, PSK);

http::HttpController* httpCtrl;

// Display Settings
UI ui;
TemperatureWidget* tempWgt = new TemperatureWidget;

// Temperature Sensor
DHTesp tsens;
thermostat::ThermostatManager* thermoManager;

void setupTemperatureWidget(){
  Point topLeft{0,0};
  Point bottomRight{34,32};
  Rectangle* boundary = new Rectangle(topLeft, bottomRight);
  tempWgt->setBoundary(boundary);
}

void setup() {
  Serial.begin(115200);
  
  Serial.println("Setting up TemperaturWidget");
  setupTemperatureWidget();
  Serial.println("Adding Temperature Widget");
  ui.getUILayout()->addWidget(tempWgt);
  Serial.println("Init UI");
  ui.init();

  tsens.setup(D6, DHTesp::DHT11);
  thermoManager = new thermostat::ThermostatManager(&tsens);

  httpCtrl = new http::HttpController(thermoManager);
  httpCtrl->registerHandlers();

  wifiman.connect();
}
/*
  MAIN LOGIC
*/
void updateTemperature(){
  thermostat::ThermostatReadings reads = thermoManager->getThermostatReadings();
  tempWgt->setHumidity(reads.humidity);
  tempWgt->setTemperature(reads.temperature);
  tempWgt->setHeatIndex(reads.heatIndex);
  Serial.printf("Temp is %.1f\nHum is %1.f\n", reads.temperature, reads.humidity);
}

void loop() {
  updateTemperature();
  Serial.println("Rendering");
  ui.render();
  delay(500);
}