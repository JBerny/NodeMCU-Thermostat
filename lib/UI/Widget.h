#ifndef WIDGET_H
#define WIDGET_H

#include <SSD1306Geometry.h>
#include <SSD1306Wire.h>

class Widget {
    protected:
        Rectangle* _boundary = NULL;
        bool drawBorder;
        void destroyBoundary();
    public:
        Rectangle* getBoundary();
        void setBoundary(Rectangle* boundary);
        void destroy() {
            destroyBoundary();
        };
        // virtual functions need to be defined at the end!!!
        virtual ~Widget();
        virtual void render(SSD1306Wire& display);
};


class TemperatureWidget : public Widget {
    private:
        float _temp = 0.0;
        float _hum = 0.0;
        float _heatIdx = 0.0;

    public:
        void render(SSD1306Wire& display);
        void setTemperature(float val);
        void setHumidity(float val);
        void setHeatIndex(float val);
        String getTemperatureString();
        String getHumidityString();
        String getHeatIndexString();
        ~TemperatureWidget();
};

#endif