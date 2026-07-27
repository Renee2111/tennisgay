#include <iostream>
#include "src/manager/YARDMANAGER/YardManager.h"
using namespace std;

int main() {

    YardManager manager("data/");
    manager.runConsole();
    return 0;
}
//cd D:\tennisgay
//g++ -std=c++17 -g main.cpp (Get-ChildItem -Recurse -Filter *.cpp src).FullName -o main.exe
//.\main.exe