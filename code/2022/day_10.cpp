//
// Created by Maarten Peels on 12/12/2022.
//

#include <iostream>
#include <vector>
#include <numeric>

void updateScore(const int &cycle, const int &x, int &part1) {
    if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
        part1 += cycle * x;
        std::cout << "cycle: " << cycle << " x: " << x << std::endl;
    }
}

void draw(const int &x, const int& cycle, std::string &part1) {
    const int offset = static_cast<int>(floor(cycle / 40) * 40);
    const size_t str_len = part1.length();
    if (str_len >= x - 1 + offset && str_len <= x + 1 + offset) {
        part1 += '#';
    } else {
        part1 += '.';
    }
}

void run_2022_10(const std::vector<std::string> &input) {
    int cycle = 1;
    int x = 1;

    int part1 = 0;
    std::string part2;


    for (const auto &line : input) {
        const std::vector<std::string> parts = Utils::split(line, ' ');

        draw(x, cycle, part2);

        if (parts[0] == "noop") {
            cycle++;
        }
        else if (parts[0] == "addx") {
            cycle++;
            updateScore(cycle, x, part1);
            draw(x, cycle, part2);
            cycle++;
            x += std::stoi(parts[1]);
        }

        updateScore(cycle, x, part1);
    }

    // Part 1
    std::cout << "Part 1: " << part1 << std::endl;

    // Part 2
    for (int i = 0; i < part2.length(); i += 40) {
        std::cout << part2.substr(i, 40) << std::endl;
    }
}
