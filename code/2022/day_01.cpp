//
// Created by Maarten Peels on 06/12/2022.
//

#include <iostream>
#include <vector>

std::vector<int> parseInput_2022_01(const std::vector<std::string>& input) {
    std::cout << "Parsing input" << std::endl;
    std::vector<int> sums;
    int current_sum = 0;
    for (const auto& line : input) {
        if (line.empty()) {
            sums.push_back(current_sum);
            current_sum = 0;
            continue;
        }

        current_sum += std::stoi(line);
    }
    sums.push_back(current_sum);
    return sums;
}

void run_2022_01(const std::vector<std::string>& input) {
    std::vector<int> sums = parseInput_2022_01(input);

    // Part 1
    int max_elem_p1 = *std::max_element(sums.begin(), sums.end());
    std::cout << "Part 1: " << max_elem_p1 << std::endl;

    // Part 2
    int largest_3_sum = 0;
    for (int i = 0; i < 3; i++) {
        auto max_elem = std::max_element(sums.begin(), sums.end());
        largest_3_sum += *max_elem;
        sums.erase(max_elem);
    }
    std::cout << "Part 2: " << largest_3_sum << std::endl;
}
