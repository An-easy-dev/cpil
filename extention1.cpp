#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include "extention1.h"
using namespace std;

int find_pos(string in){
  int pos=0;
  for(char i:in){
    if(i!=' '){
      return pos;
    }
    pos+=1;
  }
  if(pos==in.size()){
    return -1;
  }
  return 0;
}
string no_q(string input){
  string o="";
  for(char i:input){
    if (i=='\"')
      continue;
    o+=i;
    }
  return o;
}
void SetColor(int color) {
    string colorCode = "\033[" + std::to_string(color) + "m";
    cout << colorCode;
}

void ResetColor() {
    cout << "\033[0m";
}
          
vector<string> gcpi(){
  vector <string> out;
  ifstream input("/proc/cpuinfo");
  string line; 
  while(getline(input,line)){
    if(line.find("model name")!=string::npos){
      out.push_back("CPU:"+string(line.substr(line.find(":") +2)));
    }else if(line.find("flags")!=string::npos){
      if(line.find("lm")!=string::npos){
        out.push_back("64 bit support (long mode)");
      }
    }
  }
  input.close();
  return out;
}
vector <string> time(){
  vector <string> out;
  time_t current_time = time(nullptr);
  struct tm* local_time = localtime(&current_time);
  out.push_back("Time:"+string(asctime(local_time)));
  int offset_hours = local_time->tm_gmtoff / 3600;
  out.push_back( "UTC: UTC"+string((offset_hours >= 0 ? "+" : "")) + to_string(offset_hours));
  return out;
}
vector <string> memory(){
  vector <string> output;
  string buf;
  ifstream file("/proc/meminfo");
  while(getline(file,buf)){
    int p=find_pos(buf);
    size_t start_pos = buf.find(":") + 1 + p;
    if(start_pos<buf.size()){
      start_pos=buf.find(":")+1;
    }
    if(buf.find("MemTotal")!=string::npos){
      output.push_back("Memory:"+buf.substr(start_pos));
    }else if(buf.find("MemFree")!=string::npos){
      output.push_back("Free:"+buf.substr(start_pos));
    }else if(buf.find("SwapTotal")!=string::npos){
      output.push_back("Swap:"+buf.substr(start_pos));
    }
  }
  return output;
}
string os_info(){
  ifstream oi("/etc/os-release");
  string out="";
  string line="";
  while(getline(oi,line)){
    if(line.find("NAME")!=string::npos)
      out=string(line.substr(line.find("=")+1));    
      break;
  }
  oi.close();
  line=no_q(out);
  out=line;
  return out;
}
string detect_display_server() {
    // Получение переменных окружения
    const char* wayland_display = getenv("WAYLAND_DISPLAY");
    const char* x11_display = getenv("DISPLAY");

    // Проверка, какая система используется
    if (wayland_display) {
        return "Wayland (WAYLAND_DISPLAY=" + std::string(wayland_display) + ")";
    } else if (x11_display) {
        return "X11 (DISPLAY=" + std::string(x11_display) + ")";
    } else {
        return "Не удалось определить дисплейный сервер. Возможно, вы работаете в консоли.";
    }
}
