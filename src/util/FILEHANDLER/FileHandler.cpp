#include "FileHandler.h"

#include <fstream>
#include <iostream>

int FileHandler::readFile(const std::string &filename,
                          std::string *&lines)
{
    std::ifstream fin(filename);

    if(!fin.is_open()){
        lines = nullptr;
        return 0;
    }

    std::string s;
    int count = 0;

    // Đếm số dòng
    while(std::getline(fin,s))
        count++;

    fin.clear();
    fin.seekg(0);

    lines = new std::string[count];

    int i = 0;

    while(std::getline(fin,s))
        lines[i++] = s;

    fin.close();

    return count;
}

void FileHandler::writeFile(const std::string &filename,
                            std::string *lines,
                            int count)
{
    std::ofstream fout(filename);

    if(!fout.is_open()){
        std::cout<<"Khong mo duoc file "<<filename<<'\n';
        return;
    }
    for(int i=0;i<count;i++){
        fout<<lines[i];
        if(i!=count-1)
            fout<<'\n';
    }

    fout.close();
}