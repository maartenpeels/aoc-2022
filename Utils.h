//
// Created by Maarten Peels on 06/12/2022.
//

#ifndef AOC2022_UTILS_H
#define AOC2022_UTILS_H

#include <iostream>
#include <vector>
#include <sstream>

class Utils {
public:
    static std::vector<std::string> split(const std::string& s, const std::string &delimiter);
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static bool startsWith(const std::string &s, const std::string &prefix);
    static bool isUnique(const std::string &s);
    static void ltrim(std::string &s);
    static void rtrim(std::string &s);
    static void trim(std::string &s);
};


#endif //AOC2022_UTILS_H
