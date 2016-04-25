//
//  circle.cpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#include "circle.hpp"
#include <GLUT/glut.h>
#include <math.h>
#include <string>
#include <iostream>

Circle::Circle() {
    this -> setLocation(0, 0);
    this -> setSize(0, 0);
    this -> setRadius(0);
    this -> setVisible(false);
    this -> setColor(0.0, 0.0, 1.0, 1.0);
}

Circle::Circle(float x, float y, float radius, float r, float g, float b, float alpha) {
    this -> setLocation(x, y);
    this -> setSize(2 * radius, 2 * radius);
    this -> setRadius(radius);
    this -> setVisible(true);
    this -> setColor(r, g, b, alpha);
    
    this -> standartX = x;
    this -> standartY = y;
    this -> standartRadius = radius;
    this -> standartW = 2 * radius;
    this -> standartH = 2 * radius;
    this -> standartVisible = true;
    this -> standartRed = r;
    this -> standartGreen = g;
    this -> standartBlue = b;
}

Circle::Circle(const Circle& circle) {
    this -> setLocation(circle.getX(), circle.getY());
    this -> setRadius(circle.getRadius());
    this -> setVisible(circle.isVisible());
    this -> setColor(circle.getRed(), circle.getGreen(), circle.getBlue(), circle.getAlpha());
}

Circle::Circle(const Shape& circle) {
    this -> setLocation(circle.getX(), circle.getY());
    this -> setVisible(circle.isVisible());
    this -> setColor(circle.getRed(), circle.getGreen(), circle.getBlue(), circle.getAlpha());
    this -> radius = 50;
    this -> h = 100;
    this -> w = 100;
    this -> alpha = 0.2;
}

float Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(float radius) {
    this -> radius = radius;
    this -> w = 2 * radius;
    this -> h = 2 * radius;
}

void Circle::setScale(float scalef) {
    this -> setRadius(this -> getRadius() * scalef);
}

void Circle::toStandart() {
    this -> x = standartX;
    this -> y = standartY;
    this -> red = standartRed;
    this -> green = standartGreen;
    this -> blue = standartBlue;
    this -> radius = standartRadius;
    this -> alpha = standartAlpha;
}

float Circle::getMinX() const { return x - radius; }

float Circle::getMinY() const { return y - radius; }

float Circle::getMaxX() const { return x + radius; }

float Circle::getMaxY() const { return y + radius; }

void Circle::trace(Shape *object) {
    Circle *cir = new Circle(*object);
    cir -> alpha = 0.2;
    cir -> setVisible(true);
    shapesTrack.push_back(cir);
}

void Circle::draw() {
    if (this -> isVisible()){
        glEnable(GL_BLEND);   //прозрачность
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(red, green, blue, alpha);
        glBegin(GL_TRIANGLE_FAN);
        for(float angle = 0; angle <= 2 * M_PI; angle += M_PI / 30) {
            glVertex2f(x + sinf(angle) * radius, y + cosf(angle) * radius);
        }
        glEnd();
        
        for (int i = 0; i < shapesTrack.size(); i++) {
            shapesTrack[i] -> alpha = 0.2;
            shapesTrack[i] -> draw();
        }
    }
    glFlush();
}

Circle& Circle::operator=(const Circle& circle) {
    this -> setLocation(circle.getX(), circle.getY());
    this -> setRadius(circle.getRadius());
    this -> setVisible(circle.isVisible());
    this -> setColor(circle.getRed(), circle.getGreen(), circle.getBlue(), circle.getAlpha());
    return *this;
}

bool Circle::operator==(const Circle& circle) const {
    if (this -> getX() == circle.getX() && this -> getY() == circle.getY() &&
        this -> getRadius() == circle.getRadius() &&
        this -> isVisible() == circle.isVisible() &&
        this -> getRed() == circle.getRed() &&
        this -> getGreen() == circle.getGreen() &&
        this -> getBlue() == circle.getBlue() &&
        this -> getAlpha() == circle.getAlpha())
        return true;
    else
        return false;
}

void Circle::saveToFile() {
    std::ofstream out;
    out.open("/Users/admin/Desktop/lab3 чек/data11.txt", std::ios_base::app );
    out << "C" << " ";
    out << x << " " << y << " ";
    out << radius << " ";
    out << red << " " << green << " " << blue << " " << alpha << " ";
    out << visible << " ";
    out << selected << " ";
    out << std::endl;
    out.close();
    
}

void Circle::changeColor() {
    float red = rand()/(float)RAND_MAX;
    float green = rand()/(float)RAND_MAX;
    float blue = rand()/(float)RAND_MAX;
    this -> setColor(red, green, blue, alpha);
}

void Circle::move(int x, int y) {
    this -> setLocation(this -> getX() + x, this -> getY() + y);
}

void Circle::setVisible(bool visible) {
    if (visible) {
        this -> visible = true;
        this -> alpha = 1.0;
    } else {
        this -> visible = true;
        this -> alpha = 0.2;
    }
}

