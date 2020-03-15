#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <Arduino.h>

struct Point {
    uint8_t x, y;
};


class Rectangle {
    public:
        Point topLeft, bottomRight;
        Rectangle(Point p1, Point p2);
        uint8_t getWidth();
        uint8_t getHeight();
        bool intersects(Rectangle* b);
};


#endif