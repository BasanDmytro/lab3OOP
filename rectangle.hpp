//
//  rectangle.hpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include "shape.hpp"
#include "vector.hpp"
#include <fstream>

class Rectangle: public Shape {
protected:
    Vector<Shape*> shapesTrack;
public:
    Rectangle(): Shape() {};
    Rectangle(float x, float y, float w, float h): Shape(x, y, w, h, 0.0, 0.0, 1.0, 1.0) {};
    Rectangle(float x, float y, float w, float h, float r, float g, float b, float alpha):Shape(x, y, w, h, r, g, b, alpha) {};
    Rectangle(const Rectangle& rect) : Shape(rect) {};
    Rectangle(const Shape& rect) : Shape(rect) {};
    
    virtual void draw();
    virtual void saveToFile();
    virtual void toStandart();
    virtual void changeColor();
    virtual void setVisible(bool visible);
    virtual void move(int x, int y);
    
    Rectangle& operator=(const Rectangle& rect);
    bool operator==(const Rectangle& rect) const;
    
    void trace(Shape *object);
};


#endif /* rectangle_hpp */
