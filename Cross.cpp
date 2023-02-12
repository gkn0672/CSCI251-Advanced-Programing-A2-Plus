#include "Cross.h"
using namespace std;

double Cross::ComputeArea() { 
    big_rec.setArea(big_rec.ComputeArea());
    br_rec.setArea(br_rec.ComputeArea());
    bl_rec.setArea(bl_rec.ComputeArea());
    tl_rec.setArea(tl_rec.ComputeArea());
    tr_rec.setArea(tr_rec.ComputeArea());

    return big_rec.GetArea() - bl_rec.GetArea() - br_rec.GetArea() - tl_rec.GetArea() - tr_rec.GetArea();
}

bool Cross::isPointInShape(int x, int y) { 
    for(int i = 0; i < plist.size(); i++) { 
        if(plist[i]->getX() == x && plist[i]->getY() == y) {
            return false;
        } 
    }

    if(isPointOnShape(x,y)) { 
        return false;
    }

    bool in_big_rec = big_rec.isPointInShape(x,y);
    bool in_corner = tr_rec.isPointInShape(x,y) 
        || tl_rec.isPointInShape(x,y)
        || bl_rec.isPointInShape(x,y) 
        || br_rec.isPointInShape(x,y);

    if(in_big_rec){
        return (!in_corner);
    }
    return false;
}

bool Cross::isPointOnShape(int x, int y) { 
    for(int i = 0; i < plist.size(); i++) { 
        if(plist[i]->getX() == x && plist[i]->getY() == y) {
            return false;
        }
    }
    bool in_big_rec = big_rec.isPointOnShape(x,y);

    bool in_corner = tr_rec.isPointOnShape(x,y) 
    || tl_rec.isPointOnShape(x,y)
    || bl_rec.isPointOnShape(x,y) 
    || br_rec.isPointOnShape(x,y);

    return (in_big_rec^in_corner);
}

string Cross::toString() {
    ostringstream oss;
    ostringstream oss1;
    ostringstream oss2;
    string res;
    oss << "Shape[" << GetId()<< "]" << endl;
    oss << "Name            : " << GetName() << endl;
    oss << "Special Type    : ";
    if(GetContainsWarpSpace()) {
        oss << "WS" << endl;
    } else{
        oss << "NS" << endl;
    }
    if(GetArea() != -1) {
        oss << "Area            : "<< setprecision(2) << fixed <<GetArea()<<" units square" << endl;
    }

    oss << "Vertices:" << endl;
    for(int i=0; i<plist.size(); i++) {
        oss << "Point [" << i << "] : (" << plist[i]->getX() << ", " << plist[i]->getY() << ")" << endl; 
    }
    oss << endl;
    int count_in = 0;
    int count_on = 0;

    for(int i = big_rec.p1.x;i <= big_rec.p2.x;i++){
        for(int j = big_rec.p1.y;j <= big_rec.p2.y;j++){
            if(isPointOnShape(i,j)) {
                oss1 << "(" << i << ", " << j << "), ";
                count_on++;
            }
            
            if(isPointInShape(i,j)) {
                oss2 << "(" << i << ", " << j << "), ";
                count_in++;
            }
        }
    }
    oss << "Points on perimeter: ";
    if(count_on == 0) {
        oss << "none!" << endl << endl;
    } else {
        res = oss1.str();
        res.erase(res.size()-2);
        oss << res << endl << endl;
    }
    
    oss << "Points within shape: ";
    if(count_in == 0) {
        oss << "none!" << endl << endl;
    } else {
        res = oss2.str();
        res.erase(res.size()-2);
        oss << res << endl << endl;
    }
    return oss.str();
}

bool compare_pointxy(Point *a, Point *b) {
    if(a->x == b->x) {
        return a->y < b->y;
    } else {
        return a->x < b->x;
    }
}

vector<Point*> Cross::getList() {
    return fulllist;
};