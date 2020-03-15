#ifndef THERMOSTATMANAGER_H
#define THERMOSTATMANAGER_H

#include <DHTesp.h>

namespace thermostat{

    struct ThermostatReadings {
        float temperature;
        float humidity;
        float heatIndex;
    };


    class ThermostatManager {
        private:
            DHTesp* tsens;
            ThermostatReadings currentValues;
            float _threshold = 18.0;
            bool _enabled = true;

        public:
            ThermostatManager(DHTesp* dht) {
                tsens = dht;
                currentValues.temperature = 0.0;
                currentValues.humidity = 0.0;
                currentValues.heatIndex = 0.0;
            };
            ThermostatReadings getThermostatReadings();
            float getThreshold();
            void setThreshold(float t);
            bool isEnabled();
            void enable();
            void disable();
    };

}

#endif