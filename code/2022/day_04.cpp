//
// Created by Maarten Peels on 06/12/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>

struct Pair {
    std::vector<int> sections1;
    std::vector<int> sections2;
};

void calculatePairs(const std::vector<std::string>input, std::vector<Pair>& pairs) {
    for (const auto& line : input) {
        // split on ,
        auto pos = line.find(',');
        auto left = line.substr(0, pos);
        auto right = line.substr(pos + 1);
        // split on -
        auto pos1 = left.find('-');
        auto pos2 = right.find('-');
        auto left1 = std::stoi(left.substr(0, pos1));
        auto left2 = std::stoi(left.substr(pos1 + 1));
        auto right1 = std::stoi(right.substr(0, pos2));
        auto right2 = std::stoi(right.substr(pos2 + 1));

        Pair pair;
        for (int i = left1; i <= left2; i++) {
            pair.sections1.push_back(i);
        }
        for (int i = right1; i <= right2; i++) {
            pair.sections2.push_back(i);
        }

        pairs.push_back(pair);
    }
}

void run_2022_04(const std::vector<std::string>& input) {
    std::vector<Pair> pairs;
    calculatePairs(input,pairs);

    // Part 1
    int result = 0;
    for (const auto &pair : pairs) {
        std::set<int> set1(pair.sections1.begin(), pair.sections1.end());
        std::set<int> set2(pair.sections2.begin(), pair.sections2.end());

        std::vector<int> intersection;
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(intersection));

        if (intersection.size() == pair.sections1.size() || intersection.size() == pair.sections2.size()) {
            result++;
        }
    }
    std::cout << "Part 1: " << result << std::endl;

    // Part 2
    result = 0;
    for (const auto &pair : pairs) {
        std::set<int> set1(pair.sections1.begin(), pair.sections1.end());
        std::set<int> set2(pair.sections2.begin(), pair.sections2.end());

        std::vector<int> intersection;
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(intersection));

        if (!intersection.empty()) {
            result++;
        }
    }
    std::cout << "Part 2: " << result << std::endl;
}
