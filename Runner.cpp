//
// Created by Maarten Peels on 06/12/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Runner.h"
#include "InputLoader.h"

#include "code/2022/day_01.cpp"
#include "code/2022/day_02.cpp"
#include "code/2022/day_03.cpp"
#include "code/2022/day_04.cpp"
#include "code/2022/day_05.cpp"
#include "code/2022/day_06.cpp"
#include "code/2022/day_07.cpp"
#include "code/2022/day_08.cpp"
#include "code/2022/day_09.cpp"
#include "code/2022/day_10.cpp"
#include "code/2022/day_11.cpp"
#include "code/2022/day_12.cpp"
#include "code/2022/day_13.cpp"
#include "code/2022/day_14.cpp"
#include "code/2022/day_15.cpp"

typedef void (*FnPtr)(const std::vector<std::string>&);
std::map<std::string, FnPtr> run_map = {
        {"2022_01", run_2022_01},
        {"2022_02", run_2022_02},
        {"2022_03", run_2022_03},
        {"2022_04", run_2022_04},
        {"2022_05", run_2022_05},
        {"2022_06", run_2022_06},
        {"2022_07", run_2022_07},
        {"2022_08", run_2022_08},
        {"2022_09", run_2022_09},
        {"2022_10", run_2022_10},
        {"2022_11", run_2022_11},
        {"2022_12", run_2022_12},
        {"2022_13", run_2022_13},
        {"2022_14", run_2022_14},
        {"2022_15", run_2022_15},
};


void Runner::run(const std::string& year, const std::string &day, bool example_input) {
    std::cout << "Running day " << day << " of year " << year << std::endl;

    std::string filename = "../input/" + year + "/day_" + day + (example_input ? "_example" : "") + ".txt";
    std::vector<std::string> input = InputLoader::loadInput(filename);
    run_map[year + "_" + day](input);
}
