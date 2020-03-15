# Weather Station with NodeMCU

### Features
* Reads ambient temperature and humidity and sends it to ThingSpeak
* Enables/Disables temperature control via WiFi

## Secrets
To store WiFi password and SSID, create a `Secrets.h` file in the `include` folder.
Example:  
```c++
#ifndef SECRETS_H
#define SECRETS_H

const char* SSID = "YourWifiName";
const char* PSK = "YourWifiPassword";

#endif
```

## Dependencies
Add the following libraries.

[SSD1306 OLED Display](https://github.com/ThingPulse/esp8266-oled-ssd1306?utm_source=platformio&utm_medium=piohome)  
[DHT for ESPx](https://github.com/beegee-tokyo/DHTesp?utm_source=platformio&utm_medium=piohome)  