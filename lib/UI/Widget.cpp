#include <Widget.h>
#include <SSD1306Wire.h>

void Widget::destroyBoundary(){
    if (!_boundary) {
        return;
    }
    Serial.println("Deferencing boundary");
    Rectangle *sink = _boundary;
    _boundary = NULL;
    Serial.println("Destroying boundary");
    delete sink;
};

void Widget::setBoundary(Rectangle* boundary) {
    if (boundary == NULL){
        return;
    }
    _boundary = boundary;
}

Rectangle* Widget::getBoundary() {
    return _boundary;
}

void Widget::render(SSD1306Wire& display){}

Widget::~Widget() {
    destroy();
}

void TemperatureWidget::setTemperature(float val) {
    if (isnan(val)) {
        return;
    }
    _temp = val;
}

void TemperatureWidget::setHumidity(float val) {
    if (isnan(val)){
        return;
    }
    _hum = val;
}

void TemperatureWidget::setHeatIndex(float val) {
    if (isnan(val)){
        return;
    }
    _heatIdx = val;
}

const char* TEMPERATURE_FMT = "T %.1f";

String TemperatureWidget::getTemperatureString(){
    char* res = new char[8];
    if (isnan(_temp)){
        sprintf(res, TEMPERATURE_FMT, 0.0);
    } else {
        sprintf(res, TEMPERATURE_FMT, _temp);
    }
    return String(res);
}

const char* HUMIDITY_FMT = "H %.1f";

String TemperatureWidget::getHumidityString(){
    char* res = new char[8];
    if (isnan(_hum)){
        sprintf(res, HUMIDITY_FMT, 0.0);
    } else {
        sprintf(res, HUMIDITY_FMT, _hum);
    }
    return String(res);
}

const char* HEATINDEX_FMT = "A %.1f";

String TemperatureWidget::getHeatIndexString(){
    char* res = new char[8];
    if (isnan(_heatIdx)){
        sprintf(res, HEATINDEX_FMT, 0.0);
    } else {
        sprintf(res, HEATINDEX_FMT, _heatIdx);
    }
    return String(res);
}

void TemperatureWidget::render(SSD1306Wire& display) {
    Serial.println("Rendering TemperatureWidget");
    // display.drawRect(int16_t(_boundary->topLeft.x), int16_t(_boundary->topLeft.y),
    //                int16_t(_boundary->getWidth()), int16_t(_boundary->getHeight()));
    display.drawString(1, 1, getTemperatureString());
    display.drawString(1, 11, getHumidityString());
    display.drawString(1, 21, getHeatIndexString());
    Serial.println("Rendering TemperatureWidget Done");
}

TemperatureWidget::~TemperatureWidget() {
    Serial.println("Destroying TemperatureWidget");
    destroy();
    Serial.println("Destroyed TemperatureWidget");
}