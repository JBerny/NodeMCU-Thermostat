#ifndef UILAYOUT_H
#define UILAYOUT_H

#include <Widget.h>

const uint8_t MAX_WIDGETS = 8;

struct WidgetNode {
    Widget* widget = NULL;
    WidgetNode* next = NULL;
};

class UILayout {
    private:
        WidgetNode* _widgets = NULL;
        uint8_t _count = 0;
    
    public:
        ~UILayout();
        WidgetNode* getWidgets();
        void addWidget(Widget* widget);
        bool canAdd(Widget* widget);
        void render(SSD1306Wire& display);
};

#endif