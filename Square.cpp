#include "Square.h"
double Square::ComputeArea(){ 
    return (p1.x-p2.x)*(p1.x-p2.x);
}

bool Square::isPointInShape(int x, int y){ 
    if(x > p1.x && x < p2.x && y > p1.y && y < p2.y ){
        return true;
    }
    return false;
}

bool Square::isPointOnShape(int x, int y){
    if (isPointInShape(x,y)){
        return false;
    }
    if(x == p1.x || x == p2.x){
        return (y < p2.y && y > p1.y);
    }
    if(y == p1.y || y == p2.y){
        return (x < p2.x && x > p1.x);
    }
    return false;
}

string Square::toString(){
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

    for(int i = p1.x; i <= p2.x; i++){
        for(int j = p1.y; j <= p2.y; j++){
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
        oss << res << endl;
    }
    return oss.str();
}

vector<Point*> Square::getList() {
    return this->fulllist;
};