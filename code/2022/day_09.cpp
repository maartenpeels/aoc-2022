//
// Created by Maarten Peels on 11/12/2022.
//

#include <iostream>
#include <vector>
#include <numeric>

using Position = std::pair<int, int>;
struct Move {
    std::pair<int, int> direction;
    int distance;
};

std::map<char, std::pair<int, int>> directions = {
        {'L', {-1, 0}},
        {'U', {0,  1}},
        {'R', {1,  0}},
        {'D', {0,  -1}},
};

void doMove(std::vector<Position> &segments, const Move &move) {
    segments[0].first += move.direction.first;
    segments[0].second += move.direction.second;

    for (int j = 1; j < segments.size(); j++) {
        Position &current = segments[j];
        Position &previous = segments[j - 1];

        int dx = abs(previous.first - current.first);
        int dy = abs(previous.second - current.second);

        if (std::max(dx, dy) > 1) {
            if (previous.first != current.first) {
                current.first += previous.first > current.first ? 1 : -1;
            }
            if (previous.second != current.second) {
                current.second += previous.second > current.second ? 1 : -1;
            }
        }
    }
}

size_t simulate(const std::vector<Move> &moves, const int &body_size) {
    std::vector<Position> segments(body_size, {0, 0});
    std::set<std::pair<int, int>> visited = {{0, 0}};

    for (const Move move: moves) {
        for (int i = 0; i < move.distance; i++) {
            doMove(segments, move);
            visited.insert({segments.back().first, segments.back().second});
        }
    }

    return visited.size();
}

void run_2022_09(const std::vector<std::string> &input) {
    std::vector<Move> moves;
    for (const std::string &line: input) {
        moves.push_back({directions[line[0]], std::stoi(line.substr(1))});
    }

    // Part 1
    const size_t part1 = simulate(moves, 2);
    std::cout << "Part 1: " << part1 << std::endl;

    // Part 2
    const size_t part2 = simulate(moves, 10);
    std::cout << "Part 2: " << part2 << std::endl;
}
