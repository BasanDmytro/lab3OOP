
#ifndef SHAPE_H
#define SHAPE_H

class Shape {
protected:
    //location
    float x;
    float y;
    //color
    float red;
    float green;
    float blue;
    
    float standartX = 320;
    float standartY = 480;
    
    float standartAlpha = 1.0;
    
    //size
    float h;
    float w;
    
    float standartH = 50;
    float standartW = 50;
    
    //visibility
    
    bool standartVisible = true;
    
    
    float standartRed = 0;
    float standartGreen = 0;
    float standartBlue = 1;
    
    //radius
    float standartRadius = 50;
    
    
public:
    float alpha;
    bool visible;
    bool selected;
    //virtual void trace(Shape *object) = 0;
    
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
    
    Shape();
    Shape(float x, float y, float h, float w, float r, float g, float b, float alpha);
    Shape(const Shape& shape);
    
    Shape& operator=(const Shape& shape);
    bool operator==(const Shape& shape) const;
};

#endif