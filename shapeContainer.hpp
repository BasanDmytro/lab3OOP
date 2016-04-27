//
//  shapeContainer.hpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#ifndef shapeContainer_hpp
#define shapeContainer_hpp

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "vector.hpp"
#include <fstream>

class ShapeContainer: public Shape {
protected:
    Vector<Shape*> shapesTrack;
    Vector<Shape*> shapes;
public:
    bool selected;
    bool isSelected() const;
    
    Vector<Shape*> getShapes();
    
    ShapeContainer();
    
    ShapeContainer(float x, float y, float w, float h, float r, float g, float b, float alpha);
    
    ShapeContainer(Shape* shape);
    
    ShapeContainer(Vector<Shape*> xx);
    
    ~ShapeContainer();
    
    void add(Shape* shape);
    
    void remove(Shape* shape);
    
    void eraseAll();
    
    virtual void toStandart();
    
    virtual void draw();
    
    void trace(Shape *object);
    
    virtual void setScale(float scalef);
    
    virtual void saveToFile();
    
    virtual void changeColor();
    
    virtual void setVisible(bool visible);
    
    virtual void move(int x, int y);
    
    virtual void boundaryCoordinates(float &leftX, float &rightX, float &downY, float &topY);
};


#endif /* shapeContainer_hpp */
