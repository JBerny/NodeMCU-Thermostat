#include <Arduino.h>
#include <SSD1306Wire.h>
#include <UI.h>


UI::UI() {
    _display = new SSD1306Wire(I2C_DISPLAY_ADDRESS, D3, D4);
    _layout = new UILayout;
}

UI::UI(SSD1306Wire* display) {
    _display = display;
   _layout = new UILayout;
}

void UI::init() {
    _display->init();
    _display->setColor(WHITE);
}

void UI::setUILayout(UILayout* lout) {
    _layout = lout;
}

UILayout* UI::getUILayout() {
    return _layout;
}

uint16_t UI::render() {
    Serial.println("Rendering UI");
    _display->clear();
    _layout->render(*_display);
    _display->display();
    return 0;
}