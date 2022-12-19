//
// Created by Maarten Peels on 13/12/2022.
//

#include <iostream>
#include <vector>
#include <numeric>

struct Monkey {
    std::deque<long> items;
    char operation{};
    std::string value;
    int test{};
    int if_true{};
    int if_false{};
    long inspected{0};
};

long solve(std::vector<Monkey> &monkeys, const int &rounds, const int &mod) {
    for (int round = 1; round <= rounds; round++) {
        for (auto &m: monkeys) {
            while (!m.items.empty()) {
                const auto &item = m.items.front();
                m.inspected++;
                long multiplier = m.value == "old" ? item : std::stoi(m.value);
                long result = m.operation == '+' ? item + multiplier : item * multiplier;
                long new_item = rounds == 20 ? static_cast<long>(floor(result / 3)) : result % mod;
                int target_monkey = new_item % m.test == 0 ? m.if_true : m.if_false;
                monkeys[target_monkey].items.push_back(new_item);
                m.items.pop_front();
            }
        }
    }

    for (const auto &m: monkeys) {
        std::cout << "Monkey " << &m - &monkeys[0] << " inspected " << m.inspected << " items" << std::endl;
    }

    std::vector<long> inspected;
    std::transform(monkeys.begin(), monkeys.end(), std::back_inserter(inspected), [](const auto &m) { return m.inspected; });
    std::sort(inspected.begin(), inspected.end());

    return inspected[inspected.size() - 1] * inspected[inspected.size() - 2];
}

void run_2022_11(const std::vector<std::string> &input) {
    std::vector<Monkey> monkeys;
    Monkey monkey;
    for (const auto &line: input) {
        if (line.empty()) {
            std::cout << "Monkey: " << monkey.items.size() << " items, operation " << monkey.operation << ", value "
                      << monkey.value << ", test " << monkey.test << ", if_true " << monkey.if_true << ", if_false "
                      << monkey.if_false << std::endl;

            monkeys.push_back(monkey);
            monkey = {};
        }

        if (line.find("Starting items:") != std::string::npos) {
            std::string items_string = line.substr(18);
            std::vector<std::string> items = Utils::split(items_string, ',');
            for (const auto &item: items) {
                monkey.items.push_back(std::stoi(item));
            }
        } else if (line.find("Operation:") != std::string::npos) {
            std::string operation = line.substr(13);
            std::vector<std::string> parts = Utils::split(operation, ' ');
            monkey.operation = parts[3][0];
            monkey.value = parts[4];
        } else if (line.find("Test:") != std::string::npos) {
            std::string test = line.substr(8);
            std::vector<std::string> parts = Utils::split(test, ' ');
            monkey.test = std::stoi(parts[2]);
        } else if (line.find("If true:") != std::string::npos) {
            std::string if_true = line.substr(13);
            std::vector<std::string> parts = Utils::split(if_true, ' ');
            monkey.if_true = std::stoi(parts[3]);
        } else if (line.find("If false:") != std::string::npos) {
            std::string if_true = line.substr(14);
            std::vector<std::string> parts = Utils::split(if_true, ' ');
            monkey.if_false = std::stoi(parts[3]);
        }
    }

    std::cout << "Monkey: " << monkey.items.size() << " items, operation " << monkey.operation << ", value "
              << monkey.value << ", test " << monkey.test << ", if_true " << monkey.if_true << ", if_false "
              << monkey.if_false << std::endl;
    monkeys.push_back(monkey);

    int mod = 1;
    for (const auto& m : monkeys) {
        mod *= m.test;
    }

    // Part 1
    std::vector<Monkey> part1_monkeys(monkeys);
    long part1 = solve(part1_monkeys, 20, mod);
    std::cout << "Part 1: " << part1 << std::endl;

    // Part 2
    std::vector<Monkey> part2_monkeys(monkeys);
    long part2 = solve(part2_monkeys, 10000, mod);
    std::cout << "Part 2: " << part2 << std::endl;
}
