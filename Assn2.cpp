#include <iostream>
#include <string>
#include <algorithm>
#include "ShapeTwoD.h"
#include "Square.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Cross.h"
#include "algo.h"
#include "Path.h"
using namespace std;

string choice;
bool input_read = false;
bool user_exit = false;
const string student_id = "7311217";
const string student_name = "Nguyen Gia Khanh";
static int shape_id = 0;
vector <ShapeTwoD*> my_shape;
void Menu();
void HandleInput(string choice);
bool CheckInput(string input);
void ShapeInput();
void ShapeCompute();
void ShapeOut();
void ShapeSort();
bool SortAreaASC(ShapeTwoD* a, ShapeTwoD* b);
bool SortAreaDSC(ShapeTwoD* a, ShapeTwoD* b);
bool SortSpecialTypeArea(ShapeTwoD* a, ShapeTwoD* b);
int current_shape = 0;
int main(){
    Menu();
    return 0;
}

// Main menu
void Menu() {
    while(true){
        ClearScreen();
        cout << "------------------------------------" << endl;
        cout << "Student ID : " << student_id << endl;
        cout << "Student Name : " << student_name << endl;
        cout << "------------------------------------" << endl;
        cout << "Welcome to Assn2 program!" << endl;
        cout << endl;
        cout << endl;
        cout << "1) Input sensor data" << endl;
        if(input_read) {
            cout << "2) Compute area(for all records)" << endl;
            cout << "3) Print shapes report" << endl;
            cout << "4) Sort shapes report" << endl;
            cout << "5) 2D-StarFleet's path finding" << endl;
        }
        cout << "6) Exit program" << endl;
        cout << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        HandleInput(TrimSpace(choice));
        if(user_exit){
            cout << "[ Exit ]" << endl;
            ClearScreen();
            break;
        } 
    }
}

//Handle user input
void HandleInput(string choice) {
    if(choice == "1") {
        ClearScreen();
        ShapeInput(); 
    } else if((choice == "2") && (input_read)) {
        ClearScreen();
        ShapeCompute();
    } else if((choice == "3") && (input_read)) {
        ClearScreen();
        cout << "Total no. of records available = " << my_shape.size() << endl;
        cout << endl; 
        ShapeOut();
    } else if((choice == "4") && (input_read)) {
        ShapeSort();
    } else if((choice == "5")) {
        Path(my_shape);
    } else if((choice == "6")) {
        user_exit = true;
        if(input_read) {
            for(int i=0; i< my_shape.size(); i++) {
                my_shape[i]->~ShapeTwoD();
            }
        }
    } else {
        cout << "Invalid option!" << endl;
        MySleep(1);
        return;
    }
}

//Check if input is valid
bool CheckInput(string input) {
    int input_converted;
    try {
        input_converted = ConvertStringToInteger(input);
    } catch(...) {
        return false;
    }

    if(input_converted < 0) {
        return false;
    }
    return true;
}

//Handle shape input
void ShapeInput() {
    string shape_name;
    string special_type;
    int shape_size = 0;
    string input_x;
    string input_y;
    int shape_x;
    int shape_y;
    vector<Point*> point_list;
    vector<int> x_coor;
    vector<int> y_coor;
    bool cws = false;
    point_list.clear();
    cout << "[Input sensor data]" << endl;
    cout << "Please enter name of shape: ";
    cin >> shape_name;
    cout << "Please enter special type: ";
    cin >> special_type;

    if(special_type == "WS") {
        cws = true;
    } else if(special_type == "NS") {
        cws = false;
    } else {
        cout << "Invalid type!" << endl;
        MySleep(1);
        return;
    } 
    cout << endl;
    if(shape_name == "Square" || shape_name == "Rectangle") {
        shape_size = 4;
        for(int i=0; i<shape_size; i++){
            cout << "Please enter x-ordinate of pt. " << i+1 << ": ";
            cin >> input_x;
            cout << "Please enter y-ordinate of pt. " << i+1 << ": ";
            cin >> input_y;
            cout << endl;

            if(!(CheckInput(input_x)) || !(CheckInput(input_y))) {
                cout << "Invalid input" << endl;
                MySleep(1);
                return;
            }
                
            shape_x = ConvertStringToInteger(input_x);
            shape_y = ConvertStringToInteger(input_y);

            point_list.push_back(new Point(shape_x, shape_y));
            x_coor.push_back(shape_x);
            y_coor.push_back(shape_y);
        }
            
        int max_x = *max_element(x_coor.begin(), x_coor.end());
        int max_y = *max_element(y_coor.begin(), y_coor.end());
        int min_x = *min_element(x_coor.begin(), x_coor.end());
        int min_y = *min_element(y_coor.begin(), y_coor.end());

        if(shape_name == "Square") {
            my_shape.push_back(new Square("Square", cws, shape_id, point_list, Point(min_x, min_y), Point(max_x, max_y)));
        } else {
            my_shape.push_back(new Rectangle("Rectangle", cws, shape_id, point_list, Point(min_x, min_y), Point(max_x, max_y)));
        }
         
        shape_id++; 
        point_list.clear();
        x_coor.clear();
        y_coor.clear();
    } else if(shape_name == "Circle") {
        shape_size = 1;
        string cir_x;
        string cir_y;
        int c_x;
        int c_y;
        string input_radius;
        int radius;
            cout << "Please enter x-ordinate of center : ";
            cin >> cir_x;
            cout << "Please enter y-ordinate of center : ";
            cin >> cir_y;

            if(!(CheckInput(cir_x)) || !(CheckInput(cir_y))) {
                cout << "Invalid input" << endl;
                MySleep(1);
                return;
            }
            c_x = ConvertStringToInteger(cir_x);
            c_y = ConvertStringToInteger(cir_y);
            cout << endl;
            cout << "Please enter radius of circle : ";
            cin >> input_radius;
            if(!(CheckInput(input_radius))) {
                cout << "Invalid input" << endl;
                MySleep(1);
                return;
            }
            radius = ConvertStringToInteger(input_radius);
            point_list.push_back(new Point(c_x, c_y));
            my_shape.push_back(new Circle("Circle", cws, shape_id, point_list, radius));
            shape_id++;
        } else if(shape_name == "Cross") {
            shape_size = 12;
            for(int i=0; i<shape_size; i++){
                cout << "Please enter x-ordinate of pt. " << i+1 << ": ";
                cin >> input_x;
                cout << "Please enter y-ordinate of pt. " << i+1 << ": ";
                cin >> input_y;
                cout << endl;

                if(!(CheckInput(input_x)) || !(CheckInput(input_y))) {
                    cout << "Invalid input" << endl;
                    MySleep(1);
                    return;
                }
                
                shape_x = ConvertStringToInteger(input_x);
                shape_y = ConvertStringToInteger(input_y);

                point_list.push_back(new Point(shape_x, shape_y));
                x_coor.push_back(shape_x);
                y_coor.push_back(shape_y);
            }
            my_shape.push_back(new Cross("Cross", cws, shape_id, point_list));
            shape_id++;
        } else {
            cout << "Invalid shape!" << endl;
            MySleep(1);
            return;
        }
        input_read = true;
        shape_size = 0;     
        cout << "Record sucessfully stored. Going back to main menu ..." << endl;
        MySleep(1); 
}

//Compute shape area
void ShapeCompute() {
    for(int i = 0;i<my_shape.size();i++){
        my_shape[i]->setArea(my_shape[i]->ComputeArea()); 
    }
    cout << "Computation complete! ( " << my_shape.size() - current_shape << " records were updated )" << endl;
    current_shape = my_shape.size();
    MySleep(1);
}

//Print shape report
void ShapeOut() {
    for(int i = 0; i<my_shape.size(); i++){
        cout<<my_shape[i]->toString() << endl; 
    }
    Freeze();
}

//Handle shape sorting
void ShapeSort() {
    string sort_option = "";
    bool sort_valid = false;
    cout << endl;
        ClearScreen();
        while(!sort_valid){
            cout << "   a) Sort by area (ascending)" << endl;
            cout << "   b) Sort by area (descending)" << endl;
            cout << "   c) Sort by special type and area" << endl;
            cout << "Please select sort option ('q' to go to main menu): ";
            cin >> sort_option;
            sort_option = TrimSpace(sort_option);
            if(sort_option == "a") {
                sort_valid = true;
                sort(my_shape.begin(), my_shape.end(), SortAreaASC);
                ClearScreen();
                ShapeOut();
            } else if(sort_option == "b") {
                sort_valid = true;
                sort(my_shape.begin(), my_shape.end(), SortAreaDSC);
                ClearScreen();
                ShapeOut();
            } else if(sort_option == "c") {
                sort_valid = true;
                sort(my_shape.begin(), my_shape.end(), SortSpecialTypeArea);
                ClearScreen();
                ShapeOut();
            } else if(sort_option == "q") {
                return;
            } else {
                cout << "Invalid option!" << endl;
                MySleep(1);
                ClearScreen();
            }
        }
}

//Sort by area ascending
bool SortAreaASC(ShapeTwoD* a, ShapeTwoD* b) {
    return a->GetArea() < b->GetArea();
}

//Sort by area descending
bool SortAreaDSC(ShapeTwoD* a, ShapeTwoD* b) {
    return a->GetArea() > b->GetArea();
}

//Sort by special type then area
bool SortSpecialTypeArea(ShapeTwoD* a, ShapeTwoD* b) {
    if(a->GetContainsWarpSpace() == b->GetContainsWarpSpace()) {
        return a->GetArea() > b->GetArea();
    } else {
        if(a->GetContainsWarpSpace()) {
            return true;
        }
    }
    return false;
}

