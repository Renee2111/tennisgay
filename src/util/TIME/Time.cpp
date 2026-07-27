#include "Time.h"
#include <iostream>
#include <sstream>

bool Time::isLeapYear(int year){
    return (year%400==0)||(year%4==0&&year%100!=0);
}

bool Time::isValidDateTime(const std::string &datetime){

    int y,m,d,h,mi;
    char c1,c2,c3,c4;

    std::stringstream ss(datetime);

    ss>>y>>c1>>m>>c2>>d>>h>>c3>>mi;

    if(ss.fail())
        return false;

    if(c1!='-'||c2!='-')
        return false;

    if(h<0||h>23)
        return false;

    if(mi<0||mi>59)
        return false;

    if(m<1||m>12)
        return false;

    int day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(isLeapYear(y))
        day[2]=29;

    if(d<1||d>day[m])
        return false;

    return true;
}

std::string Time::inputDateTime(){

    std::string s;

    while(true){

        std::getline(std::cin,s);

        if(isValidDateTime(s))
            return s;

        std::cout<<"Sai dinh dang!\n";
        std::cout<<"Nhap lai (YYYY-MM-DD HH:MM): ";
    }
}