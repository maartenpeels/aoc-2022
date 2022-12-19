//
// Created by Maarten Peels on 13/12/2022.
//

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <variant>

void run_2022_14(const std::vector<std::string> &input) {
    int floor {0};
    std::map<std::pair<int, int>, bool> grid;

    for (const auto &line: input) {
        int last_x{0};
        int last_y{0};
        auto parts = Utils::split(line, " -> ");
        for (const auto &coord: parts) {
            const auto xy = Utils::split(coord, ",");
            const int x = std::stoi(xy.at(0));
            const int y = std::stoi(xy.at(1));

            if (y > floor) {
                floor = y;
            }

            if (last_x > 0 && last_y > 0) {
                if (last_x != x) {
                    int from_x = std::min(last_x, x);
                    int to_x = std::max(last_x, x);
                    for (int i = from_x; i <= to_x; i++) {
                        grid[{i, y}] = true;
                    }
                } else if (last_y != y) {
                    int from_y = std::min(last_y, y);
                    int to_y = std::max(last_y, y);
                    for (int i = from_y; i <= to_y; i++) {
                        grid[{x, i}] = true;
                    }
                }
            }

            last_x = x;
            last_y = y;
        }
    }

    auto grid2(grid);

    // Part 1
    int sand_x = 500;
    int sand_y = 0;
    int units = 0;
    bool sand_will_rest = true;
    while (sand_will_rest) {
        if (sand_y + 1 > floor) {
            sand_will_rest = false;
            continue;
        }

        if (grid.find({sand_x, sand_y + 1}) == grid.end()) {
            sand_y++;
            continue;
        } else if (grid.find({sand_x - 1, sand_y + 1}) == grid.end()) {
            sand_x--;
            sand_y++;
            continue;
        } else if (grid.find({sand_x + 1, sand_y + 1}) == grid.end()) {
            sand_x++;
            sand_y++;
            continue;
        } else {
            grid[{sand_x, sand_y}] = true;
            units++;
            sand_x = 500;
            sand_y = 0;
        }
    }
    std::cout << "Part 1: " << units << std::endl;

    // Part 2
    floor += 2;
    sand_x = 500;
    sand_y = 0;
    units = 0;
    sand_will_rest = true;
    while (sand_will_rest) {
        if (grid2.find({sand_x, sand_y + 1}) == grid2.end() && sand_y + 1 != floor) {
            sand_y++;
            continue;
        } else if (grid2.find({sand_x - 1, sand_y + 1}) == grid2.end() && sand_y + 1 != floor) {
            sand_x--;
            sand_y++;
            continue;
        } else if (grid2.find({sand_x + 1, sand_y + 1}) == grid2.end() && sand_y + 1 != floor) {
            sand_x++;
            sand_y++;
            continue;
        } else {
            if (sand_x == 500 && sand_y == 0) {
                sand_will_rest = false;
                units++;
                continue;
            }

            grid2[{sand_x, sand_y}] = true;
            units++;
            sand_x = 500;
            sand_y = 0;
        }
    }
    std::cout << "Part 2: " << units << std::endl;
}
