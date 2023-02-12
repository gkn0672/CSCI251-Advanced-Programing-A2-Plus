#include "Circle.h"

double Circle::ComputeArea(){
    return (double)3.14 * radius * radius;
}

bool Circle::isPointInShape(int x, int y){ 
    if(x == center->x && y == center->y){
        return false;
    }

    int d_xtocenter = center->x - x;
    int d_ytocenter = center->y - y;

    return sqrt((d_xtocenter*d_xtocenter)+(d_ytocenter*d_ytocenter)) < radius;
}

bool Circle::isPointOnShape(int x, int y){ 
    int d_xtocenter = center->x - x; 
    int d_ytocenter = center->y - y;

    return (d_xtocenter*d_xtocenter)+(d_ytocenter*d_ytocenter) == (radius*radius);
}

string Circle::toString(){
    ostringstream oss;
    ostringstream oss1;
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
    oss << "Center: (" << center->x << ", " << center->y << ")" << endl;
    oss << "Radius: " << radius << endl;
    int count_in = 0;
    int count_on = 0;

    oss << "Points on perimeter: ";
    oss << "(" << center->x - radius << ", "<< center->y << "), ";
    oss << "(" << center->x << ", " << center->y - radius << "), ";
    oss << "(" << center->x + radius << ", "<< center->y << "), ";
    oss << "(" << center->x << ", " << center->y + radius << ")" << endl << endl;
    
    int count = 0;
    for(int i = center->x-radius; i <= center->x +radius; i++){
        for(int j= center->y -radius; j <= center->y +radius; j++){
            if(isPointInShape(i,j)){
                oss1 << "(" << i << ", " << j << "), ";
                count++;
            }
        }
    }

    oss << "Points within shape: ";
    if(count == 0) {
        oss << "none!" << endl << endl;
    } else {
        res = oss1.str();
        res.erase(res.size()-2);
        oss << res << endl;
    }

    return oss.str();
}

vector<Point*> Circle::getList() {
    return plist;
}