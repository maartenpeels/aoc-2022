//
// Created by Maarten Peels on 13/12/2022.
//

#include <iostream>
#include <vector>
#include <map>
#include <numeric>

#define PRINT_COST_MAP 0

int find_cost(
        int **height_map, const size_t &height, const size_t &width,
        const size_t &start_x, const size_t &start_y,
        const size_t &target_x, const size_t &target_y) {
    int cost_map[height][width];
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            cost_map[row][col] = 1000000000;
        }
    }

    cost_map[start_y][start_x] = 0;
    std::deque<std::pair<size_t, size_t>> queue;
    queue.emplace_back(start_y, start_x);
    while (!queue.empty()) {
        auto [y, x] = queue.front();
        queue.pop_front();
        int cost = cost_map[y][x];

        // Check all neighbours
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dy == 0 && dx == 0) {
                    continue;
                }
                if (dy != 0 && dx != 0) {
                    continue;
                }

                size_t ny = y + dy;
                size_t nx = x + dx;
                if (ny >= height || nx >= width) {
                    continue;
                }

                int height_diff = height_map[ny][nx] - height_map[y][x];
                if (height_diff > 1) {
                    continue;
                }

                int new_cost = cost + 1;
                if (new_cost < cost_map[ny][nx]) {
                    cost_map[ny][nx] = new_cost;
                    queue.emplace_back(ny, nx);
                }
            }
        }
    }

#if PRINT_COST_MAP
    // Print cost map
    for (auto &row: cost_map) {
        for (auto &col: row) {
            if (col == 1000000000) {
                std::cout << "X";
            } else {
                std::cout << col << " ";
            }
        }
        std::cout << std::endl;
    }
#endif

    return cost_map[target_y][target_x];
}

void run_2022_12(const std::vector<std::string> &input) {
    size_t width = input.at(0).size();
    size_t height = input.size();
    int **height_map;

    // Allocate memory for height map
    height_map = new int *[height];
    for (size_t i = 0; i < height; i++) {
        height_map[i] = new int[width];
    }

    size_t start_x{};
    size_t start_y{};
    size_t target_x{};
    size_t target_y{};

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            char c = input.at(row).at(col);
            if (c == 'S') {
                c = 'a';
                start_x = col;
                start_y = row;
            }
            if (c == 'E') {
                c = 'z';
                target_x = col;
                target_y = row;
            }
            int h = c - 'a';
            height_map[row][col] = h;
        }
    }

    // Part 1
    int part1 = find_cost(height_map, height, width, start_x, start_y, target_x, target_y);
    std::cout << "Part 1: " << part1 << std::endl;

    // Part 2
    std::vector<std::pair<size_t, size_t>> start_points;
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            if (height_map[row][col] == 0) {
                start_points.emplace_back(row, col);
            }
        }
    }

    std::vector<int> costs;
    for (auto [y, x]: start_points) {
        int cost = find_cost(height_map, height, width, x, y, target_x, target_y);
        costs.push_back(cost);
    }

    int part2 = *std::min_element(costs.begin(), costs.end());
    std::cout << "Part 2: " << part2 << std::endl;
}
