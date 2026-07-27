#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
public:
    static int readFile(const std::string &filename, std::string *&lines);

    static void writeFile(const std::string &filename,
                          std::string *lines,
                          int count);
};

#endif