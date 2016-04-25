//
//  main.cpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#include <GLUT/glut.h>
#include "rectangle.hpp"
#include "circle.hpp"
#include "shapeContainer.hpp"
#include "vector.hpp"
#include <iostream>
#include <ctime>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

Vector<Shape*> vec;
Shape *currVecCont;

bool visibleCurr = true;
bool animateCurr = false;
bool boolForInsert = false;
bool boolForBool = false;
bool boolForCheck = true;
bool boolForTrack = false;
int winW, winH;
int countForTrack = 0;
int countForMerge = 0;
bool boolForMerge = false;
int numbersOfObgectForMerge = 0;
int countOfAgregat = 1;

Shape* setCurrentContainer(Shape *cont){
    currVecCont = cont;
    currVecCont -> setSelected(true);
    currVecCont -> setVisible(true);
    
    Vector<Shape*>::iterator it;
    for (it = vec.begin(); it < vec.end(); it++)
        if (currVecCont != (*it)) {
            //  (*it)->setSelected(false); //видимость контура
            //  (*it) -> alpha = 0.5;
            (*it) -> setVisible(false); //видимость обьекта
            //   (*it) -> alpha = 0.5;
        }
    return currVecCont;
}

Shape* selectNext() {
    if (currVecCont == vec.back())
        return setCurrentContainer(vec.front());
    else {
        unsigned long shapeSize = vec.size() - 1;
        for(int i = 0; i < shapeSize; i++) {
            if (currVecCont == vec[i])
                return setCurrentContainer(vec[i + 1]);
        }
    }
    return 0;
}

void animateCurrentShapeCont() {
    if (animateCurr) {
        currVecCont -> move(1, 1);
    }
}

void mergeShapesWithCurrent() {
    int currForMerge = 0;
    for (int i = 0; i < vec.size(); i++) {
        Shape* stepVecCont = vec[i];
        if (currVecCont == stepVecCont)
            currForMerge = i;
    }
    Vector<Shape*> vecForMerge;
    vecForMerge.push_back(vec[currForMerge]);
    vecForMerge.push_back(vec[numbersOfObgectForMerge]);
    if (currForMerge > numbersOfObgectForMerge) {
        vec.erase(currForMerge);
        vec.erase(numbersOfObgectForMerge);
    } else {
        vec.erase(numbersOfObgectForMerge);
        vec.erase(currForMerge);
        
    }
    Shape *pp = new ShapeContainer(vecForMerge);
    pp -> setSelected(true);
    vec.push_back(pp);
    setCurrentContainer(pp);
}

void changeShapes() {
    float x11 = currVecCont -> getMinX();
    float y11 = currVecCont -> getMinY();
    float x12 = currVecCont -> getMaxX();
    float y12 = currVecCont -> getMaxY();
    for (auto i = 0; i < vec.size(); i++) {
        Shape* stepShape = vec[i];
        if (currVecCont != stepShape) {
            float x21 = stepShape -> getMinX();
            float y21 = stepShape -> getMinY();
            float x22 = stepShape -> getMaxX();
            float y22 = stepShape -> getMaxY();
            if (boolForCheck)
                //проверям условия пересечения
                if (x11 < x22 && x12 > x21 && y11 < y22 && y12 > y21) {
                    if (boolForInsert == false) {
                        currVecCont -> setScale(0.5);
                        boolForInsert = true;
                        boolForCheck = false;
                    } else {
                        currVecCont -> setScale(2.0);
                        boolForInsert = false;
                        boolForCheck = false;
                    }
                }
        }
        boolForCheck = true;
    }
}

void save() {
    ofstream out;
    out.open("/Users/admin/Desktop/lab3 чек/data.txt");
    out.close();
    Vector<Shape*>::iterator it;
    for (int i = 0; i < vec.size(); i++) {
        vec[i] -> saveToFile();
    }
}

void loadFromFile() {
    ifstream in;
    auto countOfString = 0;
    char S;
    in.open("/Users/admin/Desktop/lab3 чек/data.txt");
    while(!in.eof()) {
        in.get(S);
        if (S == '\n') {
            countOfString++;
        }
    }
    in.close();
    auto ii = 0;
    string *str = new string[countOfString];
    ifstream fin1("/Users/admin/Desktop/lab3 чек/data.txt");
    while (fin1) {
        getline(fin1, str[ii]);
        ii++;
    }
    fin1.close();
    for (int i = 0; i < countOfString; i++) {
        string name = "";
        string name2 = "";
        int x = 0;
        int y = 0;
        int h = 0;
        int w = 0;
        int radius = 0;
        float red = 0;
        float green = 0;
        float blue = 0;
        float alpha = 0;
        if (str[i][0] == 'A') {
            Vector<string> arr1;
            Vector<string> arr2;
            Vector<Shape*> vecForMerge;
            string delim(" ");
            size_t prev = 0;
            size_t next;
            size_t delta = delim.length();
            string delim1(" ");
            size_t prev1 = 0;
            size_t next1;
            size_t delta1 = delim1.length();
            while( ( next = str[i + 1].find( delim, prev ) ) != string::npos ){
                arr1.push_back( str[i + 1].substr( prev, next-prev ) );
                prev = next + delta;
            }
            arr1.push_back( str[i + 1].substr( prev ) );
            
            while( ( next1 = str[i + 2].find( delim1, prev1 ) ) != string::npos ){
                arr2.push_back( str[i + 2].substr( prev1, next1-prev1 ) );
                prev1 = next1 + delta1;
            }
            arr2.push_back( str[i + 2].substr( prev1 ) );
            name = arr1[0];
            name2 = arr2[0];
            if (name == "C") {
                x = stoi(arr1[1]);
                y = stoi(arr1[2]);
                radius = stoi(arr1[3]);
                red = stof(arr1[4]);
                green = stof(arr1[5]);
                blue = stof(arr1[6]);
                alpha = stof(arr1[7]);
                Shape *shape1 = new Circle(x, y, radius, red, green, blue, alpha);
                vecForMerge.push_back(shape1);
            } else if (name == "R") {
                x = stoi(arr1[1]);
                y = stoi(arr1[2]);
                h = stoi(arr1[3]);
                w = stoi(arr1[4]);
                red = stof(arr1[5]);
                green = stof(arr1[6]);
                blue = stof(arr1[7]);
                alpha = stof(arr1[8]);
                Shape *shape1 = new Rectangle(x, y, h, w, red, green, blue, alpha);
                vecForMerge.push_back(shape1);
            }
            if (name2 == "C") {
                x = stoi(arr2[1]);
                y = stoi(arr2[2]);
                radius = stoi(arr2[3]);
                red = stof(arr2[4]);
                green = stof(arr2[5]);
                blue = stof(arr2[6]);
                alpha = stof(arr2[7]);
                Shape *shape2 = new Circle(x, y, radius, red, green, blue, alpha);
                vecForMerge.push_back(shape2);
            } else if (name2 == "R") {
                x = stoi(arr2[1]);
                y = stoi(arr2[2]);
                h = stoi(arr2[3]);
                w = stoi(arr2[4]);
                red = stof(arr2[5]);
                green = stof(arr2[6]);
                blue = stof(arr2[7]);
                alpha = stof(arr2[8]);
                Shape *shape2 = new Rectangle(x, y, h, w, red, green, blue, alpha);
                vecForMerge.push_back(shape2);
            }
            Shape *pp = new ShapeContainer(vecForMerge);
            if (alpha == 0.2) {
                pp -> setSelected(false);
                pp -> setVisible(false);
            } else {
                pp -> setSelected(true);
                pp -> setVisible(true);
            }
            vec.push_back(pp);
            str[i + 1] = "";
            str[i + 2] = "";
        }
        if (str[i][0] == 'C') {
            Vector<string> arr;
            string delim(" ");
            size_t prev = 0;
            size_t next;
            size_t delta = delim.length();
            while( ( next = str[i].find( delim, prev ) ) != string::npos ){
                arr.push_back( str[i].substr( prev, next-prev ) );
                prev = next + delta;
            }
            arr.push_back( str[i].substr( prev ) );
            x = stof(arr[1]);
            y = stof(arr[2]);
            radius = stof(arr[3]);
            red = stof(arr[4]);
            green = stof(arr[5]);
            blue = stof(arr[6]);
            alpha = stof(arr[7]);
            Shape *shape = new Circle(x, y, radius, red, green, blue, alpha);
            if (alpha == 0.2) {
                shape -> setSelected(false);
                shape -> setVisible(false);
            } else {
                shape -> setSelected(true);
                shape -> setVisible(true);
            }
            vec.push_back(shape);
        } else if (str[i][0] == 'R') {
            Vector<string> arr;
            string delim(" ");
            size_t prev = 0;
            size_t next;
            size_t delta = delim.length();
            while( ( next = str[i].find( delim, prev ) ) != string::npos ){
                arr.push_back( str[i].substr( prev, next-prev ) );
                prev = next + delta;
            }
            arr.push_back( str[i].substr( prev ) );
            x = stof(arr[1]);
            y = stof(arr[2]);
            h = stof(arr[3]);
            w = stof(arr[4]);
            red = stof(arr[5]);
            green = stof(arr[6]);
            blue = stof(arr[7]);
            alpha = stof(arr[8]);
            Shape *shape1 = new Rectangle(x, y, h, w, red, green, blue, alpha);
            if (alpha == 0.2) {
                shape1 -> setSelected(false);
                shape1 -> setVisible(false);
            } else {
                shape1 -> setSelected(true);
                shape1 -> setVisible(true);
            }
            vec.push_back(shape1);
        }
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Vector<Shape*>::iterator it;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] != currVecCont) {
            vec[i] -> draw();
        }
    }
    if (currVecCont != NULL) currVecCont -> draw();
    animateCurrentShapeCont();
    glutSwapBuffers();
}

void resizeWindow(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

void idle(){
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == '1') {
        Shape *newShape = new Rectangle(winW / 2, winH / 2, 50, 50, 0.0, 0.0, 1.0, 1.0);
        newShape -> setVisible(true);
        vec.push_back(newShape);
        setCurrentContainer(newShape);
    } else if (key == '2') {
        Shape *newCont = new Circle(winW / 2, winH / 2, 50, 0.0, 0.0, 1.0, 1.0);
        newCont -> setVisible(true);
        vec.push_back(newCont);
        setCurrentContainer(newCont);
    } else if ((int)key == 9) {
        selectNext();
    } else if (key == 'm' || key == 'M') {
        mergeShapesWithCurrent();
    } else if (key == 'c' || key == 'C') {
        currVecCont -> changeColor();
    } else if (key == 'p' || key == 'P') {
        if (animateCurr) {
            animateCurr = false;
        } else {
            animateCurr = true;
        }
    } else if (key == 'z' || key == 'Z') {
        currVecCont -> setScale(2.0);
    } else if(key == 'h' || key == 'H') {
        if (visibleCurr) {
            currVecCont -> setVisible(false);
            currVecCont -> setSelected(false);
            visibleCurr = false;
        } else {
            currVecCont -> setVisible(true);
            currVecCont -> setSelected(true);
            visibleCurr = true;
        }
    } else if (key == 'x' || key == 'X') {
        currVecCont -> setScale(0.5);
    } else if (key == 'q' || key == 'Q') {
        save();
        
    } else if (key == 's' || key == 'S') {
        currVecCont -> toStandart();
    } else if (key == 'l' || key == 'l') {
        loadFromFile();
    } else if (key == 't' || key == 'T') {
        countForTrack++;
        if (countForTrack % 2 == 1) {
            boolForTrack = true;
        } else {
            boolForTrack = false;
        }
    } else if ((int)key == 61) {
        for (int i = 0; i < vec.size(); i++) {
            Shape* stepVecCont = vec[i];
            if (currVecCont == stepVecCont)
                numbersOfObgectForMerge = i;
        }
    }
}

void processSpecialKeys(int key, int x, int y) {
    if (key == 101) {
        if (boolForTrack) {
            currVecCont -> move(0, 10);
            currVecCont -> trace(currVecCont);
        } else {
            currVecCont -> move(0, 10);
        }
        changeShapes();
    }
    else if (key == 102) {
        if (boolForTrack) {
            currVecCont -> move(10, 0);
            currVecCont -> trace(currVecCont);
        } else {
            currVecCont -> move(10, 0);
        }
        changeShapes();
    }
    else if (key == 103) {
        if (boolForTrack) {
            currVecCont -> move(0, -10);
            currVecCont -> trace(currVecCont);
        } else {
            currVecCont -> move(0, -10);
        }
        changeShapes();
    }
    else if (key == 100) {
        if (boolForTrack) {
            currVecCont -> move(-10, 0);
            currVecCont -> trace(currVecCont);
        } else {
            currVecCont -> move(-10, 0);
        }
        changeShapes();
    }
}

int main (int argc, char ** argv) {
    srand(time_t(NULL));
    glutInit(&argc, argv);
    winW = 640; winH = 480;
    Shape *shapes = new Circle(winW / 2, winH / 2, 50, 0.0, 0.0, 1.0, 1.0);
    shapes -> setVisible(true);
    shapes -> setSelected(true);
    vec.push_back(shapes);
    setCurrentContainer(shapes);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Lab3_OOP");
    glutDisplayFunc(render);
    glutIdleFunc(idle);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glDisable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
