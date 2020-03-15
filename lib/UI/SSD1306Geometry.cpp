#include <SSD1306Geometry.h>

Rectangle::Rectangle(Point topLeft, Point bottomRight){
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

bool Rectangle::intersects(Rectangle* b){
   return (! (b->bottomRight.x < topLeft.x) || // b is at the left of this
        (b->bottomRight.y < topLeft.y ) ||// b is above this
        (b->topLeft.x < bottomRight.x) || // b is at the right of this
        (b->topLeft.y < bottomRight.y) // b is under this
   );
}

uint8_t Rectangle::getWidth(){
    return topLeft.x + bottomRight.x;
}

uint8_t Rectangle::getHeight(){
    return topLeft.y + bottomRight.y;
}