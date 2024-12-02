#ifndef EXTENTION_H
#define EXTENTION_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
using namespace std;
void SetColor(int color);
void ResetColor();
vector<string> gcpi();
vector <string> memory();
string os_info();
int find_pos(string in);
vector <string> time();
string detect_display_server();
#endif
