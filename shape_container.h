
#ifndef SHAPE_CONTAINER_H
#define SHAPE_CONTAINER_H

#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "Vector.h"
#include <fstream>

class ShapeContainer: public Shape {
protected:
    Vector<Shape*> shapesTrack;
    Vector<Shape*> shapes;
public:
    
    bool selected;
    
    bool isSelected() const;
    
    void setSelected(bool selected);
    
    Vector<Shape*> getShapes();
    
    void recalculateBounds1();
    
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
    
    virtual void recalculateBounds();
    
    virtual void saveToFile();
    
    virtual void changeColor();
    
    virtual void setVisible(bool visible);
    
    virtual void move(int x, int y);
};

#endif