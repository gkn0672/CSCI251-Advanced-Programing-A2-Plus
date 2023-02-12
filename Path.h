#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <string>
#include "Point.h"
#include "ShapeTwoD.h"
#include "Square.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Cross.h"

using namespace std;

class Node {
    public:
        int x;
        int y;
        bool walkable;
        bool iswrap;
        bool visited;
        int gcost;
        int hcost;
        vector<int> parent;

        Node() {
        }

        int getFcost() {
            return gcost + hcost;
        }
};

void Path(vector <ShapeTwoD*> my_shape);
#endif
