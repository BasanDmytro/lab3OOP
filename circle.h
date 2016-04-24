#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <vector>
#include <fstream>

class Circle: public Shape {
protected:
    float radius;
    float standartRadius;
    std::vector<Shape*> shapesTrack;
public:
    float getRadius() const;
    void setRadius(float radius);
    
    virtual void saveToFile();
    
    virtual float getMinX() const;
    virtual float getMinY() const;
    virtual float getMaxX() const;
    virtual float getMaxY() const;    
    
    Circle();
    Circle(float x, float y, float radius, float r, float g, float b, float alpha);
    Circle(const Circle& circle);
    
    Circle(const Shape& circle);
    virtual void draw();
    virtual void setScale(float scalef);
    
    virtual void trace(Shape *object);
    
    virtual void toStandart();
    
    virtual void move(int x, int y);
    
    virtual void changeColor();
    
    virtual void setVisible(bool visible);
    
    Circle& operator = (const Circle& circle);
    bool operator == (const Circle& circle) const;
};

#endif