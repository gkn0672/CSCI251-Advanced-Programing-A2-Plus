#ifndef RECTANGLE_H
#define RECTANGLE_H

#include<algorithm>
#include<cmath>
#include<iomanip>
#include<iostream>
#include<sstream>
#include<string.h>
#include<vector>

#include "ShapeTwoD.h"
#include "Point.h"

using namespace std;

class Rectangle:public ShapeTwoD{
    public:
        vector<Point*> plist;
        vector<Point*> fulllist;
        Point p1;
        Point p2;
        Rectangle(){};
        Rectangle(string name, bool cws, int id, vector<Point*>alist, Point p1, Point p2)
        :ShapeTwoD("Rectangle", cws , id) {
            plist = alist;
            fulllist = alist;
            this->p1 = p1;
            this->p2 = p2; 
            for(int i = p1.x; i <= p2.x; i++){
                for(int j = p1.y; j <= p2.y; j++){
                    if(isPointOnShape(i,j) || isPointInShape(i,j)) {
                        fulllist.push_back(new Point(i, j));
                    }  
                }
            }
        }
        Rectangle(bool cws, Point p1, Point p2) 
        :ShapeTwoD("SpecialRect", cws, -1) {
            this->p1 = p1;
            this->p2 = p2;
        }
        double ComputeArea();
        string toString();
        bool isPointInShape(int x,int y);
        bool isPointOnShape(int x,int y);
        vector<Point*> getList();
        ~Rectangle() {
            for(int i=0; i<fulllist.size(); i++) {
                delete fulllist[i]; 
            }
        }
};

#endif