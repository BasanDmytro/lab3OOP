//
//  shapeContainer.cpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#include "shapeContainer.hpp"
#include <GLUT/GLUT.h>
#include <iostream>

ShapeContainer::ShapeContainer():Shape() {
    this -> setSelected(false);
    this -> setColor(0.0, 0.0, 1.0, 1.0);
}

ShapeContainer::ShapeContainer(float x, float y, float w, float h, float r, float g, float b, float alpha) : Shape(x, y, w, h, r, g, b, alpha) {
    this -> setSelected(true);
    this -> setScale(2.0);
}

ShapeContainer::ShapeContainer(Shape* shape) {
    this -> setVisible(true);
    this -> selected = true;
    this -> setColor(0.0, 0.0, 1.0, 0.5);
    this -> add(shape);
}

ShapeContainer::ShapeContainer(Vector<Shape*> xx) {
    for (int i = 0; i < xx.size(); ++i) {
        shapes.push_back(xx[i]);
    }
}

void ShapeContainer::eraseAll() {
    unsigned long shapesSize = shapes.size();
    for(int i = 0; i < shapesSize; i++)
        delete shapes[i];
}

ShapeContainer::~ShapeContainer() { }

void ShapeContainer::setScale(float scalef) {
    unsigned long shapesSize = shapes.size();
    for(int i = 0; i < shapesSize; i++)
        shapes[i] -> setScale(scalef);
}

void ShapeContainer::toStandart() {
    unsigned long shapesSize = shapes.size();
    for(int i = 0; i < shapesSize; i++)
        shapes[i] -> toStandart();
    this -> setColor(1.0, 1.0, 0.0, 1.0);
    this -> setSize(2 * standartRadius, 2 * standartRadius);
}

bool ShapeContainer::isSelected() const {
    return this -> selected;
}

Vector<Shape*> ShapeContainer::getShapes() {
    return this -> shapes;
}

void ShapeContainer::add(Shape* shape) {
    this -> shapes.push_back(shape);
    if (shapes.size() > 1)
        shape -> setColor(shapes[0] -> getRed(), shapes[0] -> getGreen(), shapes[0] -> getBlue(), shapes[0] -> getAlpha());
}

void ShapeContainer::remove(Shape* shape) {
    for (int i = 0; i < shapes.size(); i++)
        if (shapes[i] == shape) shapes.erase(i);
}

void ShapeContainer::move(int x, int y) {
    this -> setLocation((this -> x) + x, (this -> y) + y);
    for (int i = 0; i < shapes.size(); i++)
        shapes[i] -> move(x, y);
}

void ShapeContainer::trace(Shape *object) {
    ShapeContainer *cir = new ShapeContainer(object);
    for (int i = 0; i <= cir -> shapes.size(); i++) {
        shapes[i] -> trace(shapes[i]);
    }
}

void ShapeContainer::draw() {
    if (this -> isVisible()){
        for (int i = 0; i < shapes.size(); i++) {
            shapes[i] -> draw();
        }
    }
    glFlush();
}

void ShapeContainer::setVisible(bool visible) {
    if (visible) {
        this -> visible = true;
        this -> alpha = 1.0;
    } else {
        this -> visible = true;
        this -> alpha = 0.2;
    }
    for (int i = 0; i < shapes.size(); i++)
        shapes[i] -> setVisible(visible);
}

void ShapeContainer::saveToFile() {
    std::ofstream out;
    out.open("/Users/admin/Desktop/C++/Лабы по ООП/lab3/data.txt", std::ios_base::app );
    out << "A" << std::endl;
    out.close();
    out.open("/Users/admin/Desktop/C++/Лабы по ООП/lab3/data.txt", std::ios_base::app );
    for (int i = 0; i < shapes.size(); i++)
        shapes[i] -> saveToFile();
    out.close();
}

void ShapeContainer::changeColor() {
    float red = rand()/(float)RAND_MAX;
    float green = rand()/(float)RAND_MAX;
    float blue = rand()/(float)RAND_MAX;
    this -> setColor(red, green, blue, alpha);
    for (int i = 0; i < shapes.size(); i++)
        shapes[i] -> setColor(red, green, blue, alpha);
}

void ShapeContainer::boundaryCoordinates(float &leftX, float &rightX, float &downY, float &topY) {
    float left, right, down, top;
    shapes[0]->boundaryCoordinates(leftX, rightX, downY, topY);
    for(int i = 0; i< shapes.size(); i++) {
        shapes[i] -> boundaryCoordinates(left, right, down, top);
        leftX = left < leftX ? left : leftX;
        rightX = right > rightX ? right : rightX;
        downY = down < downY ? down : downY;
        topY = top > topY ? top : topY;
    }
}