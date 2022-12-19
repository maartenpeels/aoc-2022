//
// Created by Maarten Peels on 06/12/2022.
//

#include "Utils.h"

std::vector<std::string> Utils::split(const std::string &s, const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    size_t found = s.find(delimiter, pos);

    while (found != std::string::npos) {
        auto token = s.substr(pos, found - pos);
        tokens.push_back(token);
        pos = found + delimiter.length();
        found = s.find(delimiter, pos);
    }

    tokens.push_back(s.substr(pos));
    return tokens;
}

std::vector<std::string> Utils::split(const std::string& s, char delimiter) {
    std::string str(1, delimiter);
    return split(s, str);
}

bool Utils::startsWith(const std::string &s, const std::string &prefix) {
    return s.rfind(prefix, 0) == 0;
}

void Utils::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void Utils::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Utils::trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

bool Utils::isUnique(const std::string &s) {
    bool unique = true;

    for (std::string::size_type i = 0; i < s.size() && unique; i++) {
        std::string::size_type j = 0;
        while (j < i && s[j] != s[i]) ++j;

        unique = j == i;
    }

    return unique;
}
