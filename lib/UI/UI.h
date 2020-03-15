#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <SSD1306Wire.h>
#include <UILayout.h>

const int I2C_DISPLAY_ADDRESS = 0x3c;

class UI {
    private:
        UILayout* _layout;
        SSD1306Wire* _display;

    public:
        int screenW = 128;
        int screenH = 64;
        UI();
        UI(SSD1306Wire* display);
        void init();
        uint16_t render();
        void setUILayout(UILayout* lout);
        UILayout* getUILayout();
};




#endif