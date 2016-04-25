#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include "Vector.h"
#include <fstream>

class Rectangle: public Shape {
protected:
    Vector<Shape*> shapesTrack;
public:
    Rectangle(): Shape() {};
    
    void trace(Shape *object);
    
    Rectangle(float x, float y, float w, float h): Shape(x, y, w, h, 0.0, 0.0, 1.0, 1.0) {};
    
    Rectangle(float x, float y, float w, float h, float r, float g, float b, float alpha):Shape(x, y, w, h, r, g, b, alpha) {};
    
    Rectangle(const Rectangle& rect) : Shape(rect) {};
    
    Rectangle(const Shape& rect) : Shape(rect) {};

    virtual void draw();
    
    Rectangle& operator=(const Rectangle& rect);
    
    bool operator==(const Rectangle& rect) const;
    
    virtual void saveToFile();
    
    virtual void toStandart();
    
    virtual void changeColor();
    
    virtual void setVisible(bool visible);
    
    virtual void move(int x, int y);
};

#endif