//
// Created by Maarten Peels on 06/12/2022.
//

#include <iostream>
#include <string>
#include <vector>

void run_2022_02(const std::vector<std::string>& input) {
    // A = rock, B = paper, C = scissors
    // X = rock, Y = paper, Z = scissors
    // X = lose, Y = draw,  Z = win
    // Elf  | Me    | Result    | Points
    // A    | Y     | Win       | 6+2=8
    // A    | X     | Draw      | 3+1=4
    // A    | Z     | Lose      | 0+3=3
    // B    | Y     | Draw      | 3+2=5
    // B    | X     | Lose      | 0+1=1
    // B    | Z     | Win       | 6+3=9
    // C    | Y     | Lose      | 0+2=2
    // C    | X     | Win       | 6+1=7
    // C    | Z     | Draw      | 3+3=6

    std::map<std::string, int> points_map_p1 = {
            {"A Y", 8}, {"B Y", 5}, {"C Y", 2},
            {"A X", 4}, {"B X", 1}, {"C X", 7},
            {"A Z", 3}, {"B Z", 9},  {"C Z", 6},
    };

    std::map<std::string, int> points_map_p2 = {
            {"A Y", 4}, {"B Y", 5}, {"C Y", 6},
            {"A X", 3}, {"B X", 1}, {"C X", 2},
            {"A Z", 8}, {"B Z", 9},  {"C Z", 7},
    };

    int points_p1 = 0;
    int points_p2 = 0;
    for (const auto& line : input) {
        if (line.empty()) {
            continue;
        }

        points_p1 += points_map_p1[line];
        points_p2 += points_map_p2[line];
    }

    std::cout << "Part 1: " << points_p1 << std::endl;
    std::cout << "Part 2: " << points_p2 << std::endl;
}
