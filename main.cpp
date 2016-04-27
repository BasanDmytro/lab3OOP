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
Shape *currShape;

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

Shape* setCurrentShape(Shape *cont){
    currShape = cont;
    currShape -> setSelected(true);
    currShape -> setVisible(true);
    Vector<Shape*>::iterator it;
    for (it = vec.begin(); it < vec.end(); it++)
        if (currShape != (*it)) {
            //  (*it)->setSelected(false); //видимость контура
            (*it) -> setVisible(false); //видимость обьекта
        }
    return currShape;
}

Shape* selectNext() {
    if (currShape == vec.back())
        return setCurrentShape(vec.front());
    else {
        unsigned long shapeSize = vec.size() - 1;
        for(int i = 0; i < shapeSize; i++) {
            if (currShape == vec[i])
                return setCurrentShape(vec[i + 1]);
        }
    }
    return 0;
}

void findCollisions() {
    for(int i = 0; i < vec.size(); i++) {
        if (boolForCheck) {
            if (currShape -> collided(vec[i]) && vec[i] != currShape) {
                if (boolForInsert == false) {
                    currShape -> setScale(0.5);
                    boolForInsert = true;
                    boolForCheck = false;
                } else {
                    currShape -> setScale(2.0);
                    boolForInsert = false;
                    boolForCheck = false;
                }
            }
            boolForCheck = true;
        }
    }
}

void animateCurrentShape() {
    if (animateCurr) {
         if (boolForTrack) {
             currShape -> move(1, 1);
             currShape -> trace(currShape);
             findCollisions();
         } else {
             currShape -> move(1, 1);
             findCollisions();
         }
    }
}

void mergeShapes() {
    int currForMerge = 0;
    for (int i = 0; i < vec.size(); i++) {
        Shape* stepVecCont = vec[i];
        if (currShape == stepVecCont)
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
    setCurrentShape(pp);
}

void save() {
    ofstream out;
    out.open("/Users/admin/Desktop/C++/Лабы по ООП/lab3/data.txt");
    out.close();
    for (int i = 0; i < vec.size(); i++) {
        vec[i] -> saveToFile();
    }
}

void loadFromFile() {
    ifstream in;
    int countOfString = 0;
    char S;
    in.open("/Users/admin/Desktop/C++/Лабы по ООП/lab3/data.txt");
    while(!in.eof()) {
        in.get(S);
        if (S == '\n') {
            countOfString++;
        }
    }
    in.close();
    int countForReadFromFile = 0;
    string *str = new string[countOfString + 1];
    ifstream fin1("/Users/admin/Desktop/C++/Лабы по ООП/lab3/data.txt");
    while (fin1) {
        getline(fin1, str[countForReadFromFile]);
        countForReadFromFile++;
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
            Vector<string> arrayForSplitInVectorFirst;
            Vector<string> arrayForSplitInVectorSecond;
            Vector<Shape*> vecForMerge;
            string delim(" ");
            unsigned long prev = 0;
            unsigned long next;
            unsigned long delta = delim.length();
            string delim1(" ");
            unsigned long prev1 = 0;
            unsigned long next1;
            unsigned long delta1 = delim1.length();
            while( ( next = str[i + 1].find( delim, prev ) ) != string::npos ){
                arrayForSplitInVectorFirst.push_back( str[i + 1].substr( prev, next - prev ) );
                prev = next + delta;
            }
            arrayForSplitInVectorFirst.push_back( str[i + 1].substr( prev ) );
            
            while( ( next1 = str[i + 2].find( delim1, prev1 ) ) != string::npos ){
                arrayForSplitInVectorSecond.push_back( str[i + 2].substr( prev1, next1 - prev1 ) );
                prev1 = next1 + delta1;
            }
            arrayForSplitInVectorSecond.push_back( str[i + 2].substr( prev1 ) );
            name = arrayForSplitInVectorFirst[0];
            name2 = arrayForSplitInVectorSecond[0];
            if (name == "C") {
                x = stoi(arrayForSplitInVectorFirst[1]);
                y = stoi(arrayForSplitInVectorFirst[2]);
                radius = stoi(arrayForSplitInVectorFirst[3]);
                red = stof(arrayForSplitInVectorFirst[4]);
                green = stof(arrayForSplitInVectorFirst[5]);
                blue = stof(arrayForSplitInVectorFirst[6]);
                alpha = stof(arrayForSplitInVectorFirst[7]);
                Shape *circle = new Circle(x, y, radius, red, green, blue, alpha);
                vecForMerge.push_back(circle);
            } else if (name == "R") {
                x = stoi(arrayForSplitInVectorFirst[1]);
                y = stoi(arrayForSplitInVectorFirst[2]);
                h = stoi(arrayForSplitInVectorFirst[3]);
                w = stoi(arrayForSplitInVectorFirst[4]);
                red = stof(arrayForSplitInVectorFirst[5]);
                green = stof(arrayForSplitInVectorFirst[6]);
                blue = stof(arrayForSplitInVectorFirst[7]);
                alpha = stof(arrayForSplitInVectorFirst[8]);
                Shape *rectangle = new Rectangle(x, y, h, w, red, green, blue, alpha);
                vecForMerge.push_back(rectangle);
            }
            if (name2 == "C") {
                x = stoi(arrayForSplitInVectorSecond[1]);
                y = stoi(arrayForSplitInVectorSecond[2]);
                radius = stoi(arrayForSplitInVectorSecond[3]);
                red = stof(arrayForSplitInVectorSecond[4]);
                green = stof(arrayForSplitInVectorSecond[5]);
                blue = stof(arrayForSplitInVectorSecond[6]);
                alpha = stof(arrayForSplitInVectorSecond[7]);
                Shape *circle = new Circle(x, y, radius, red, green, blue, alpha);
                vecForMerge.push_back(circle);
            } else if (name2 == "R") {
                x = stoi(arrayForSplitInVectorSecond[1]);
                y = stoi(arrayForSplitInVectorSecond[2]);
                h = stoi(arrayForSplitInVectorSecond[3]);
                w = stoi(arrayForSplitInVectorSecond[4]);
                red = stof(arrayForSplitInVectorSecond[5]);
                green = stof(arrayForSplitInVectorSecond[6]);
                blue = stof(arrayForSplitInVectorSecond[7]);
                alpha = stof(arrayForSplitInVectorSecond[8]);
                Shape *rectangle = new Rectangle(x, y, h, w, red, green, blue, alpha);
                vecForMerge.push_back(rectangle);
            }
            Shape *shapeContainer = new ShapeContainer(vecForMerge);
            if (alpha == 0.2) {
                shapeContainer -> setSelected(false);
                shapeContainer -> setVisible(false);
            } else {
                shapeContainer -> setSelected(true);
                shapeContainer -> setVisible(true);
            }
            vec.push_back(shapeContainer);
            str[i + 1] = "";
            str[i + 2] = "";
        }
        if (str[i][0] == 'C') {
            Vector<string> vectorForSplitString;
            string delim(" ");
            unsigned long prev = 0;
            unsigned long next;
            unsigned long delta = delim.length();
            while( ( next = str[i].find( delim, prev ) ) != string::npos ){
                vectorForSplitString.push_back( str[i].substr( prev, next - prev ) );
                prev = next + delta;
            }
            vectorForSplitString.push_back( str[i].substr( prev ) );
            x = stof(vectorForSplitString[1]);
            y = stof(vectorForSplitString[2]);
            radius = stof(vectorForSplitString[3]);
            red = stof(vectorForSplitString[4]);
            green = stof(vectorForSplitString[5]);
            blue = stof(vectorForSplitString[6]);
            alpha = stof(vectorForSplitString[7]);
            Shape *circle = new Circle(x, y, radius, red, green, blue, alpha);
            if (alpha == 0.2) {
                circle -> setSelected(false);
                circle -> setVisible(false);
            } else {
                circle -> setSelected(true);
                circle -> setVisible(true);
            }
            vec.push_back(circle);
        } else if (str[i][0] == 'R') {
            Vector<string> vectorForSplitString;
            string delim(" ");
            unsigned long prev = 0;
            unsigned long next;
            unsigned long delta = delim.length();
            while( ( next = str[i].find( delim, prev ) ) != string::npos ){
                vectorForSplitString.push_back( str[i].substr( prev, next - prev ) );
                prev = next + delta;
            }
            vectorForSplitString.push_back( str[i].substr( prev ) );
            x = stof(vectorForSplitString[1]);
            y = stof(vectorForSplitString[2]);
            h = stof(vectorForSplitString[3]);
            w = stof(vectorForSplitString[4]);
            red = stof(vectorForSplitString[5]);
            green = stof(vectorForSplitString[6]);
            blue = stof(vectorForSplitString[7]);
            alpha = stof(vectorForSplitString[8]);
            Shape *rectangle = new Rectangle(x, y, h, w, red, green, blue, alpha);
            if (alpha == 0.2) {
                rectangle -> setSelected(false);
                rectangle -> setVisible(false);
            } else {
                rectangle -> setSelected(true);
                rectangle -> setVisible(true);
            }
            vec.push_back(rectangle);
            setCurrentShape(rectangle);
        }
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Vector<Shape*>::iterator it;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] != currShape) {
            vec[i] -> draw();
        }
    }
    if (currShape != NULL) currShape -> draw();
    animateCurrentShape();
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

void idle() {
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == '1') {
        Shape *newRectangle = new Rectangle(winW / 2, winH / 2, 50, 50, 0.0, 0.0, 1.0, 1.0);
        newRectangle -> setVisible(true);
        vec.push_back(newRectangle);
        setCurrentShape(newRectangle);
    } else if (key == '2') {
        Shape *newCircle = new Circle(winW / 2, winH / 2, 50, 0.0, 0.0, 1.0, 1.0);
        newCircle -> setVisible(true);
        vec.push_back(newCircle);
        setCurrentShape(newCircle);
    } else if ((int)key == 9) {
        selectNext();
    } else if (key == 'm' || key == 'M') {
        mergeShapes();
    } else if (key == 'c' || key == 'C') {
        currShape -> changeColor();
    } else if (key == 'p' || key == 'P') {
        if (animateCurr) {
            animateCurr = false;
        } else {
            animateCurr = true;
        }
    } else if (key == 'z' || key == 'Z') {
        currShape -> setScale(2.0);
    } else if(key == 'h' || key == 'H') {
        if (visibleCurr) {
            currShape -> setVisible(false);
            currShape -> setSelected(false);
            visibleCurr = false;
        } else {
            currShape -> setVisible(true);
            currShape -> setSelected(true);
            visibleCurr = true;
        }
    } else if (key == 'x' || key == 'X') {
        currShape -> setScale(0.5);
    } else if (key == 'q' || key == 'Q') {
        save();
    } else if (key == 's' || key == 'S') {
        currShape -> toStandart();
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
            if (currShape == stepVecCont)
                numbersOfObgectForMerge = i;
        }
    }
}

void processSpecialKeys(int key, int x, int y) {
    if (key == 101) {
        if (boolForTrack) {
            currShape -> move(0, 10);
            currShape -> trace(currShape);
        } else {
            currShape -> move(0, 10);
        }
        findCollisions();
    }
    else if (key == 102) {
        if (boolForTrack) {
            currShape -> move(10, 0);
            currShape -> trace(currShape);
        } else {
            currShape -> move(10, 0);
        }
        findCollisions();
    }
    else if (key == 103) {
        if (boolForTrack) {
            currShape -> move(0, -10);
            currShape -> trace(currShape);
        } else {
            currShape -> move(0, -10);
        }
        findCollisions();
    }
    else if (key == 100) {
        if (boolForTrack) {
            currShape -> move(-10, 0);
            currShape -> trace(currShape);
        } else {
            currShape -> move(-10, 0);
        }
        findCollisions();
    }
}

int main (int argc, char ** argv) {
    srand(time_t(NULL));
    glutInit(&argc, argv);
    winW = 640; winH = 480;
    Shape *circle = new Circle(winW / 2, winH / 2, 50, 0.0, 0.0, 1.0, 1.0);
    circle -> setVisible(true);
    circle -> setSelected(true);
    vec.push_back(circle);
    setCurrentShape(circle);
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
