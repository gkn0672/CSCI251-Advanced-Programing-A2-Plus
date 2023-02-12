#include "ShapeTwoD.h"

string ShapeTwoD::GetName() {
    return name;
}

bool ShapeTwoD::GetContainsWarpSpace() {
    return containsWarpSpace;
}

int ShapeTwoD::GetId() {
    return id;
}

double ShapeTwoD::GetArea() {
    return area;
}

void ShapeTwoD::setArea(double area) {
    this->area = area;
}

void ShapeTwoD::setContainsWarpSpace(bool cws) {
    containsWarpSpace = cws;
}

void ShapeTwoD::setId(int id) {
    this->id = id;
}

void ShapeTwoD::setName(string name) {
    this->name = name;
}

double ShapeTwoD::ComputeArea() {
    return 0.0;
}

string ShapeTwoD::toString() {
}

ShapeTwoD::~ShapeTwoD() {

}

vector<Point*> ShapeTwoD::getList() {
    
}

