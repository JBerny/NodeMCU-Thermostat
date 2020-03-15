#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>


WiFiManager::WiFiManager(const char* ssid, const char* pwd) {
    _ssid = ssid;
    _pwd = pwd;
    _retries = 10;
}

bool WiFiManager::connected(){
    return WiFi.status() == WL_CONNECTED;
}

bool WiFiManager::connect() {
    WiFi.begin(_ssid, _pwd);
    Serial.printf("Connecting to %s...\n", _ssid);
    uint8 i = 0;
    while (!connected() || i < _retries) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.println(++i);
        if (connected()) {
            Serial.println("Connection established!");
            Serial.println(WiFi.localIP());       
            return true;
        }
    }
    Serial.println("Not connected. Give up.");
    return false;
}