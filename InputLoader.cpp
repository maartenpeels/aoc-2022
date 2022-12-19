//
// Created by Maarten Peels on 06/12/2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "InputLoader.h"

std::vector <std::string> InputLoader::loadInput(std::string filename) {
    std::vector<std::string> input;
    std::ifstream file;
    file.open(filename);
    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }
    return input;
}
