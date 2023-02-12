#ifndef POINT_H
#define POINT_H

#include<iostream>
#include<string>

using namespace std;

class Point {
    public:
        int x;
        int y;

        int getX();
        int getY();
        void setX(int x);
        void setY(int y);

        Point() {
            x = -1;
            y = -1;
        }
        
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }
};
#endif