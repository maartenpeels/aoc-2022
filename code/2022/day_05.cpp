//
// Created by Maarten Peels on 07/12/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "../../Utils.h"

struct Move_05 {
    int amount {};
    int from {};
    int to {};
};

void parseInput_2022_05(std::map<int, std::vector<char>> &stacks, std::vector<Move_05> &moves, const std::vector<std::string> &input) {
    for (const auto &line: input) {
        if (line.find("[") != std::string::npos) {
            for (int i = 0; i < line.size(); i+=4) {
                if (stacks.find(i/4 + 1) == stacks.end()) {
                    std::vector<char> stack;
                    stacks[i/4 + 1] = stack;
                }

                auto chunk = line.substr(i, 4);
                Utils::trim(chunk);
                if (!chunk.empty()) {
                     stacks[i/4 + 1].emplace_back(chunk[1]);
                }
            }
        }

        if (line.find("move") != std::string::npos) {
            auto move = Move_05();
            auto parts = Utils::split(line, ' ');
            move.amount = std::stoi(parts[1]);
            move.from = std::stoi(parts[3]);
            move.to = std::stoi(parts[5]);
            moves.emplace_back(move);
        }
    }

    for (auto &stack: stacks) {
        std::vector<char> &t = stack.second;
        std::reverse(t.begin(), t.end());
    }
}

void run_2022_05(const std::vector<std::string>& input) {
    std::map<int, std::vector<char>> stacks;
    std::vector<Move_05> moves;
    parseInput_2022_05(stacks, moves, input);

    std::map<int, std::vector<char>> stacks2 {stacks};

    // Part 1
    for (const auto &move: moves) {
        auto &from = stacks[move.from];
        auto &to = stacks[move.to];
        for (int i = 0; i < move.amount; i++) {
            to.emplace_back(from.back());
            from.pop_back();
        }
    }

    std::string part1;
    for (const auto &stack: stacks) {
        part1 += stack.second.back();
    }
    std::cout << "Part 1: " << part1 << std::endl;

    // Part 2
    for (const auto &move: moves) {
        // move 2 from 2 to 1
        auto &from = stacks2[move.from];
        auto &to = stacks2[move.to];
        to.insert(to.end(), from.end() - move.amount, from.end());
        from.erase(from.end() - move.amount, from.end());
    }

    std::string part2;
    for (const auto &stack: stacks2) {
        part2 += stack.second.back();
    }
    std::cout << "Part 2: " << part2 << std::endl;
}
