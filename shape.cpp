//
//  shape.cpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#include "shape.hpp"

void  Shape::setVisible(bool visible) { }

void Shape::draw() { };

void Shape::changeColor() { }

void Shape::toStandart() { }

void Shape::move(int x, int y) { }

void Shape::saveToFile() { }

Shape::Shape() {
    this -> setLocation(0, 0);
    this -> setSize(0, 0);
    this -> setVisible(false);
    this -> setColor(0.0, 0.0, 0.0, 1.0);
}

Shape::Shape(float x, float y, float w, float h, float r, float g, float b, float alpha) {
    this -> setLocation(x, y);
    this -> setSize(w, h);
    this -> setVisible(true);
    this -> standartX = x;
    this -> standartY = y;
    this -> standartW = w;
    this -> standartH = h;
    this -> standartVisible = true;
    this -> standartRed = r;
    this -> standartGreen = g;
    this -> standartBlue = b;
    this -> setColor(r, g, b, alpha);
}

Shape::Shape(const Shape& shape) {
    this -> setLocation(shape.x, shape.y);
    this -> setSize(shape.getHeight(), shape.getWidth());
    this -> setColor(shape.getRed(), shape.getGreen(), shape.getBlue(), shape.getAlpha());
    this -> setVisible(shape.isVisible());
}

void  Shape::setLocation(float x, float y) {
    this -> x = x;
    this -> y = y;
}

float Shape::getWidth() const{ return w; }

float Shape::getHeight() const{ return h; }

void  Shape::setSize(float w, float h){
    this -> h = h;
    this -> w = w;
}

bool  Shape::isVisible() const { return visible; }

float Shape::getRed() const { return red; }

float Shape::getGreen() const { return green; }

float Shape::getBlue() const { return blue; }

float Shape::getAlpha() const { return alpha; }

void  Shape::setColor(float r, float g, float b, float alpha) {
    this -> red = r;
    this -> green = g;
    this -> blue = b;
    this -> alpha = alpha;
}

Shape& Shape::operator=(const Shape& shape) {
    this -> setLocation(shape.x, shape.y);
    this -> setSize(shape.getHeight(), shape.getWidth());
    this -> setColor(shape.getRed(), shape.getGreen(), shape.getBlue(), shape.getAlpha());
    this -> setVisible(shape.isVisible());
    return *this;
}

void Shape::setScale(float scalef) {
    this -> h *= scalef;
    this -> w *= scalef;
}

bool Shape::operator==(const Shape& shape) const {
    if (this -> x == shape.x && this -> y == shape.y &&
        this -> getWidth() == shape.getWidth() && this -> getHeight() == shape.getHeight() &&
        this -> isVisible() == shape.isVisible() &&
        this -> getRed() == shape.getRed() &&
        this -> getGreen() == shape.getGreen() &&
        this -> getBlue() == shape.getBlue() &&
        this -> getAlpha() == shape.getAlpha())
        return true;
    else
        return false;
}

void Shape::setSelected(bool selected) {
    this -> selected = selected;
}

void Shape::boundaryCoordinates(float &leftX, float &rightX, float &downY, float &topY) {
    leftX = x;
    rightX = x + w;
    downY = y;
    topY = y + h;
}

bool Shape::collided(Shape *shape) {
    float left, right, down, top;
    boundaryCoordinates(left, right, down, top);
    float l, r, d, t;
    shape->boundaryCoordinates(l, r, d, t);
    if (r > left &&
        l < right &&
        t > down &&
        d < top)
        return true;
    return false;
}
