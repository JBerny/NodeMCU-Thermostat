#include <ESP8266WiFi.h>

class WiFiManager {
    private:
        const char* _ssid;
        const char* _pwd;
        uint8 _retries;

    public:
        WiFiManager(const char* ssid, const char* pwd);
        bool connect();
        bool connected();
        void setRetryAttempts(uint8 nr);

};