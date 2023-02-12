#ifndef CROSS_H
#define CROSS_H

#include<algorithm>
#include<cmath>
#include<iomanip>
#include<iostream>
#include<sstream>
#include<string.h>
#include<vector>

#include "ShapeTwoD.h"
#include "Point.h"
#include "Rectangle.h"
#include "Square.h"

using namespace std;

bool compare_pointxy(Point *a, Point *b);
class Cross: public ShapeTwoD{
    public:
        vector<Point*> plist;
        vector<Point*> fulllist;
        Rectangle big_rec;
        Rectangle bl_rec;
        Rectangle br_rec;
        Rectangle tl_rec;
        Rectangle tr_rec;

        Cross(){};
        Cross(string name, bool cws, int id, vector<Point*>alist)
        :ShapeTwoD("Cross", cws, id) {
            plist = alist;
            fulllist = alist;
            sort(alist.begin(), alist.end(), compare_pointxy);
            big_rec = Rectangle(cws, Point(alist[0]->x, alist[2]->y), Point(alist[11]->x, alist[9]->y));
            bl_rec  = Rectangle(cws, Point(alist[0]->x, alist[2]->y), Point(alist[3]->x, alist[3]->y));
            tl_rec = Rectangle(cws, Point(alist[1]->x, alist[1]->y), Point(alist[5]->x, alist[5]->y));
            br_rec = Rectangle(cws, Point(alist[6]->x, alist[6]->y), Point(alist[10]->x, alist[10]->y));
            tr_rec = Rectangle(cws, Point(alist[8]->x, alist[8]->y), Point(alist[11]->x, alist[9]->y));
            
            for(int i = big_rec.p1.x;i <= big_rec.p2.x;i++){
                for(int j = big_rec.p1.y;j <= big_rec.p2.y;j++){
                    if(isPointOnShape(i,j) || isPointInShape(i, j)) {
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
        ~Cross() {
            for(int i=0; i<fulllist.size(); i++) {
                delete this->fulllist[i]; 
            }
        }
};
#endif