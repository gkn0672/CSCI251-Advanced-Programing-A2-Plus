#ifndef CIRCLE_H
#define CIRCLE_H

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


class Circle: public ShapeTwoD{
    public:
        vector<Point*> plist;
        Point* center;
        int radius;

        Circle(){};
        Circle(string name, bool cws, int id, vector<Point*>alist, int radius)
        :ShapeTwoD("Circle", cws, id){
            plist = alist;
            center = plist[0];
            this->radius = radius;
            plist.push_back(new Point(center->x - radius, center->y));
            plist.push_back(new Point(center->x, center->y - radius));
            plist.push_back(new Point(center->x + radius, center->y));
            plist.push_back(new Point(center->x, center->y + radius));
            for(int i = center->x-radius; i <= center->x +radius; i++){
                for(int j= center->y -radius; j <= center->y +radius; j++){
                    if(isPointInShape(i,j)){
                        plist.push_back(new Point(i, j));
                    }
                }
            }
        }

        double ComputeArea();
        string toString();
        bool isPointInShape(int x,int y);
        bool isPointOnShape(int x,int y);
        vector<Point*> getList();
        ~Circle() {
            cout << "Delete circle" << endl;
            for(int i=0; i<plist.size(); i++) {
                delete plist[i]; 
            }
        }
};
#endif