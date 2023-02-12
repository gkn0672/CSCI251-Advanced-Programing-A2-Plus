#ifndef ALGO_H
#define ALGO_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
using namespace std;

vector <string> ReadFile(string name);
vector<string> ProcessString(string input, string splitby);

string TrimSpace(string str);

int ConvertStringToInteger(string s);

void GenerateStringMap(string** arr, int width, int height);
void GenerateIntegerMap(int** arr, int width, int height);
void Render(string** arr, int width, int height);
void Freeze();
void DeleteStringMap(string** arr, int height);
void DeleteIntMap(int** arr, int height);
void MySleep(int amount);
void ClearScreen();
#endif