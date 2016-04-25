//
//  circle.hpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#ifndef circle_hpp
#define circle_hpp

#include "shape.hpp"
#include "vector.hpp"
#include <fstream>

class Circle: public Shape {
protected:
    float radius;
    float standartRadius;
    Vector<Shape*> shapesTrack;
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

#endif /* circle_hpp */
