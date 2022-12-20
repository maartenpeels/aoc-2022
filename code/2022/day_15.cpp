//
// Created by Maarten Peels on 13/12/2022.
//

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <variant>

struct point {
    int x;
    int y;
    int d{};

    bool operator==(const point &other) const {
        return x == other.x && y == other.y && d == other.d;
    }
};

bool pointInList(const std::vector<point> &l, int x, int y) {
    for (const auto &hay: l) {
        if (hay.x == x && hay.y == y) {
            return true;
        }
        return false;
    }
}

bool possible(int x, int y, const std::vector<point> &sensors, const std::vector<point> &beacons) {
    return std::all_of(sensors.begin(), sensors.end(), [&](const point &sensor) {
        return std::abs(x - sensor.x) + std::abs(y - sensor.y) > sensor.d || pointInList(beacons, x, y);
    });
}

void run_2022_15(const std::vector<std::string> &input) {
    std::vector<point> sensors;
    std::vector<point> beacons;

    for (const auto &line: input) {
        const auto parts = Utils::split(line, ' ');
        const int pos_x = std::stoi(parts.at(2).substr(2, parts.at(2).length() - 3));
        const int pos_y = std::stoi(parts.at(3).substr(2, parts.at(3).length() - 3));
        const int beacon_x = std::stoi(parts.at(8).substr(2, parts.at(8).length() - 3));
        const int beacon_y = std::stoi(parts.at(9).substr(2));

        int distance = std::abs(pos_x - beacon_x) + std::abs(pos_y - beacon_y);
        sensors.push_back({pos_x, pos_y, distance});
        beacons.push_back({beacon_x, beacon_y});
    }

    // Part 1
    int count{0};
    int check_y = 2000000;
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    for (const auto &sensor: sensors) {
        min_x = std::min(min_x, sensor.x - sensor.d);
        max_x = std::max(max_x, sensor.x + sensor.d);
    }

    for (int x = min_x; x <= max_x; ++x) {
        if (!possible(x, check_y, sensors, beacons) && !pointInList(beacons, x, check_y)) {
            count++;
        }
    }
    std::cout << "Part 1: " << count - 1 << std::endl;

    // Part 2 (Solved with hints)
    for (const auto &sensor: sensors) {
        for (int dx = 0; dx < sensor.d + 2; dx++) {
            int dy = (sensor.d + 1) - dx;
            for (const std::pair<int, int> &m: std::vector<std::pair<int, int>>{{-1, 1},
                                                                                {1,  -1},
                                                                                {-1, -1},
                                                                                {1,  1}}) {
                int x = sensor.x + (dx * m.first);
                int y = sensor.y + (dy * m.second);

                if (0 <= x && x <= 4000000 && 0 <= y && y <= 4000000 && possible(x, y, sensors, beacons)) {
                    long result = static_cast<long>(x) * 4000000 + static_cast<long>(y);
                    std::cout << "Part 2: " << result << std::endl;
                    return;
                }
            }
        }
    }
}
