#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include "extention1.h"
using namespace std;

enum colors:int{
black=30,
red=31,
green=32,
yellow=33,
blue=34,
magenta=35,
cyan=36,
white=37,
orange=93
};

void name(string fname,int color){
    ifstream y(fname);
    string lines="";
    SetColor(color);
    while(getline(y,lines)){
      cout<<lines<<endl;
    }
    ResetColor();
    y.close();
}
int main(){
  string display=detect_display_server();
  cout<<display<<endl;
  vector<vector<string>> out;
  out.push_back(gcpi());
  out.push_back(memory());
  vector <string> time_inf=time();
  string os=os_info();
  cout<<"OS:"<<os<<endl;
  transform(os.begin(),os.end() , os.begin() , ::tolower);
  if(os.find("zorin os")!=string::npos){
    name("zorin.txt",cyan);
  }else if(os.find("ubuntu")!=string::npos){
    name("ubuntu.txt",orange);
  }
  for(uint8_t i=0;i<out.size();i++){
    for(uint8_t k=0;k<out[i].size();k++)
      cout<<out[i][k]<<endl;  
  }
  return 0;
}
