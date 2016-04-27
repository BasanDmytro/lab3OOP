//
//  shape.hpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#ifndef shape_hpp
#define shape_hpp

class Shape {
protected:
    //location
    float x;
    float y;
    //size
    float h;
    float w;
    //color
    float red;
    float green;
    float blue;
    
    float standartX = 320;
    float standartY = 480;
    float standartAlpha = 1.0;
    float standartH = 50;
    float standartW = 50;
    bool standartVisible = true;
    float standartRed = 0;
    float standartGreen = 0;
    float standartBlue = 1;
    float standartRadius = 50;
public:
    float alpha;
    bool visible;
    bool selected;
    
    virtual void saveToFile();
    
    float getX() const;
    float getY() const;
    void setLocation(float x, float y);
    
    float getWidth() const;
    float getHeight() const;
    void setSize(float h, float w);
    
    //bounds
    virtual float getMinX() const;
    virtual float getMinY() const;
    virtual float getMaxX() const;
    virtual float getMaxY() const;
    
    bool isVisible() const;
    
    virtual void setVisible(bool visible);
    
    float getRed() const;
    float getBlue() const;
    float getGreen() const;
    float getAlpha() const;
    
    virtual void changeColor();
    
    void setColor(float r, float g, float b, float alpha);
    
    virtual void trace(Shape *object) = 0;
    
    virtual void toStandart();
    
    void setSelected(bool selected);
    
    void moveWithTrack(float dx, float dy);
    
    virtual void draw();
    
    virtual void setScale(float scalef);
    
    virtual void move(int x, int y);
    
    virtual void boundaryCoordinates(float &leftX, float &rightX, float &downY, float &topY);
    
    virtual bool collided(Shape *shape);
    
    Shape();
    Shape(float x, float y, float h, float w, float r, float g, float b, float alpha);
    Shape(const Shape& shape);
    
    Shape& operator=(const Shape& shape);
    bool operator==(const Shape& shape) const;
};


#endif /* shape_hpp */
