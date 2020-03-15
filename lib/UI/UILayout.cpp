#include <UILayout.h>

WidgetNode* UILayout::getWidgets() {
    return _widgets;
}

bool UILayout::canAdd(Widget* widget) {
    //TODO add check for boundaries
    return MAX_WIDGETS >= _count;
}

void UILayout::addWidget(Widget* newWidget) {
    if (!canAdd(newWidget)) {
        return;
    } 
    if (!newWidget) {
        return;
    }
    Serial.printf("Adding widget %p\n", newWidget);
    WidgetNode* head = new WidgetNode;
    head->next = _widgets;
    head->widget = newWidget;
    _widgets = head;
    _count++;
}

void UILayout::render(SSD1306Wire& display) {
    Serial.println("Rendering UILayout");
    WidgetNode *current = _widgets;
    while (current->widget) {
        Widget *widget = current->widget;
        widget->render(display);
        if (current->next) {
            current = current->next;
        } else {
            break;
        }       
    }
}

UILayout::~UILayout() {
    Serial.println("Destroying UILayout");
    WidgetNode *current = _widgets;
    while (current) {
        if (current->widget) {
            current->widget->~Widget();
        }
        current = current->next;
    }
}