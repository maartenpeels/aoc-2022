//
// Created by Maarten Peels on 10/12/2022.
//

#include <iostream>
#include <vector>
#include <numeric>


void run_2022_08(const std::vector<std::string> &input) {
    int width = static_cast<int>(input[0].length());
    int height = static_cast<int>(input.size());
    int* trees = new int[width * height];
    int* visible = new int[width * height];
    int* scenic_scores = new int[width * height];

    int idx = 0;
    for (const auto &line : input) {
        for (const auto &c : line) {
            trees[idx++] = c - '0';
        }
    }

    for (int i = 0; i < height; i++) { // Row
        for (int j = 0; j < width; j ++) { // Col
            size_t arr_idx = i * width + j;
            int top = 0;
            int left = 0;
            int right = 0;
            int bottom = 0;

            // Check all the trees above
            bool above_visible = true;
            for (int k = i - 1; k >= 0; k--) {
                size_t check_idx = k * width + j;
                top++;
                if (trees[check_idx] >= trees[arr_idx]) {
                    above_visible = false;
                    break;
                }
            }

            // Check all the trees to the left
            bool left_visible = true;
            for (int k = j - 1; k >= 0; k--) {
                size_t check_idx = i * width + k;
                left++;
                if (trees[check_idx] >= trees[arr_idx]) {
                    left_visible = false;
                    break;
                }
            }

            // Check all the trees to the right
            bool right_visible = true;
            for (int k = j + 1; k < width; k++) {
                size_t check_idx = i * width + k;
                right++;
                if (trees[check_idx] >= trees[arr_idx]) {
                    right_visible = false;
                    break;
                }
            }

            // Check all the trees below
            bool below_visible = true;
            for (int k = i + 1; k < height; k++) {
                size_t check_idx = k * width + j;
                bottom++;
                if (trees[check_idx] >= trees[arr_idx]) {
                    below_visible = false;
                    break;
                }
            }

            scenic_scores[arr_idx] = top * left * right * bottom;

            if (above_visible || left_visible || right_visible || below_visible) {
                visible[arr_idx] = 1;
            } else {
                visible[arr_idx] = 0;
            }
        }
    }

    // Part 1
    int visible_count = std::accumulate(visible, visible + width * height, 0);
    std::cout << "Part 1: " << visible_count << std::endl;

    // Part 2
    int max_scenic_score = 0;
    for (size_t i = 0; i < width * height; i++) {
        if (scenic_scores[i] > max_scenic_score) {
            max_scenic_score = scenic_scores[i];
        }
    }
    std::cout << "Part 2: " << max_scenic_score << std::endl;

    delete[] trees;
    delete[] visible;
}
