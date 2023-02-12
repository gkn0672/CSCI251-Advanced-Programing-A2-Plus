#ifndef SQUARE_H
#define SQUARE_H

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

class Square:public ShapeTwoD{
    public:
        vector<Point*> plist; 
        vector<Point*> fulllist;
        Point p1;
        Point p2;
        Square(){};
        Square(string name, bool cws, int id, vector<Point*>alist, Point p1, Point p2)
        :ShapeTwoD("Square", cws, id) {
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
        double ComputeArea();
        string toString();
        bool isPointInShape(int x,int y);
        bool isPointOnShape(int x,int y);
        vector<Point*> getList();
    ~Square() {
        for(int i=0; i<fulllist.size(); i++) {
            delete fulllist[i]; 
        }
    }
};
#endif