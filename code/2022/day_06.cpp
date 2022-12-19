//
// Created by Maarten Peels on 08/12/2022.
//

#include <iostream>
#include <vector>

int detectStart(const std::string &data, int window_size) {
    int result{};
    for (int i = 0; i < data.length() - window_size + 1; i++) {
        result++;
        std::string chunk = data.substr(i, window_size);
        if (Utils::isUnique(chunk)) {
            return result + window_size - 1;
        }
    }
    return 0;
}

void run_2022_06(const std::vector<std::string> &input) {
    // Part 1
    int p1_sliding_window_size = 4;
    std::cout << "Part 1: " << detectStart(input[0], p1_sliding_window_size) << std::endl;

    // Part 2
    int p2_sliding_window_size = 14;
    std::cout << "Part 2: " << detectStart(input[0], p2_sliding_window_size) << std::endl;
}
