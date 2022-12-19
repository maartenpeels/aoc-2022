//
// Created by Maarten Peels on 09/12/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <deque>

void goBack(std::deque<int> &stack, std::vector<int> &sizes) {
    sizes.push_back(stack.back());
    stack.pop_back();

    if (!stack.empty()) {
        stack.back() += sizes.back();
    }
}

void run_2022_07(const std::vector<std::string> &input) {
    std::deque<int> stack;
    std::vector<int> sizes;

    for (const auto &line: input) {
        auto parts = Utils::split(line, ' ');
        if (parts[0] == "$") {
            if (parts[1] == "cd") {
                if (parts[2] == "..") {
                    goBack(stack, sizes);
                } else {
                    stack.push_back(0);
                }
            }
        } else if (parts[0] != "dir") {
            stack.back() += std::stoi(parts[0]);
        }
    }

    while (!stack.empty()) {
        goBack(stack, sizes);
    }

    // Part 1
    int result = 0;
    int maxSize = 0;
    for (const auto &size: sizes) {
        if (size > maxSize)
            maxSize = size;
        if (size <= 100000)
            result += size;
    }
    std::cout << "Part 1: " << result << std::endl;

    // Part 2
    int min = maxSize;
    for (const auto &size: sizes) {
        if (size >= maxSize - 40000000)
            min = std::min(min, size);
    }
    std::cout << "Part 2: " << min << std::endl;
}
