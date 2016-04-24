#include "rectangle.h"
#include <math.h>
#include <ctime>
#include <GLUT/glut.h>
#include <iostream>

void Rectangle::draw(){
    if (this -> isVisible()){
        glEnable(GL_BLEND);   //прозрачность
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(red, green, blue, alpha);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + h);
        glVertex2f(x + w, y + h);
        glVertex2f(x + w, y);
        glEnd();
    }
    for (int i = 0; i < shapesTrack.size(); i++) {
        shapesTrack[i] -> alpha = 0.2;
        shapesTrack[i] -> draw();
    }
    glFlush();
}

void Rectangle::trace(Shape *object) {
    Rectangle *rec = new Rectangle(*object);
    rec -> setVisible(true);
    rec -> alpha = 0.2;
    shapesTrack.push_back(rec);
}

Rectangle& Rectangle::operator=(const Rectangle& rect) {
    this -> setLocation(rect.getX(), rect.getY());
    this -> setSize(rect.getWidth(), rect.getHeight());
    this -> setColor(rect.getRed(), rect.getGreen(), rect.getBlue(), rect.getAlpha());
    this -> setVisible(rect.isVisible());
    return *this;    
}

bool Rectangle::operator==(const Rectangle& rect) const {
    if (this -> getX() == rect.getX() && this -> getY() == rect.getY() &&
        this -> getWidth() == rect.getWidth() && this -> getHeight() == rect.getHeight() &&
        this -> isVisible() == rect.isVisible() &&
        this -> getRed() == rect.getRed() &&
        this -> getGreen() == rect.getGreen() &&
        this -> getBlue() == rect.getBlue() &&
        this -> getAlpha() == rect.getAlpha())
        return true;
    else
        return false;
}

void Rectangle::saveToFile() {
    std::ofstream out;
    out.open("/Users/admin/Desktop/lab3 чек/data11.txt", std::ios_base::app );
    out << "R" << " ";
    out << x << " " << y << " ";
    out << h << " " << w << " ";
    out << red << " " << green << " " << blue << " " << alpha << " ";
    out << visible << " ";
    out << selected << " ";
    out << std::endl;
    out.close();
}

void Rectangle::changeColor() {
    float red = rand()/(float)RAND_MAX;
    float green = rand()/(float)RAND_MAX;
    float blue = rand()/(float)RAND_MAX;
    this -> setColor(red, green, blue, alpha);
}

void Rectangle::toStandart() {
    this -> x = standartX;
    this -> y = standartY;
    this -> red = standartRed;
    this -> green = standartGreen;
    this -> blue = standartBlue;
    this -> w = standartW;
    this -> h = standartH;
    this -> alpha = standartAlpha;
}

void Rectangle::setVisible(bool visible) {
    if (visible) {
        this -> visible = true;
        this -> alpha = 1.0;
    } else {
        this -> visible = true;
        this -> alpha = 0.2;
    }
}

void Rectangle::move(int x, int y) {
    this -> setLocation(this -> getX() + x, this -> getY() + y);
}