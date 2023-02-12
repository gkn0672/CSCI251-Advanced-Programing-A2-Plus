#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Point.h"
using namespace std;

class ShapeTwoD{
    protected:
        string name;
        bool containsWarpSpace = false;
        double area = -1;
        int id;
    public:
        ShapeTwoD(){};
        ShapeTwoD(string name, bool containsWrapSpace, int id){
            this->name = name;
            this->containsWarpSpace = containsWrapSpace;
            this->id = id;
        }

        string GetName();
        int GetId();
        bool GetContainsWarpSpace();
        double GetArea();

        virtual double ComputeArea();
        virtual bool IsPointInShape(int x, int y){};
        virtual bool IsPointOnShape(int x, int y){};
        
        void setName(string name);
        virtual void setId(int id);
        virtual void setArea(double area);
        void setContainsWarpSpace(bool containWrapSpace);
        virtual vector<Point*> getList();
        virtual string toString();
        virtual ~ShapeTwoD();
};
#endif