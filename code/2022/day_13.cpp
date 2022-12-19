//
// Created by Maarten Peels on 13/12/2022.
//

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <variant>

struct packet_t : std::vector<std::variant<int, packet_t>> {
    using std::vector<std::variant<int, packet_t>>::vector;
};

using packets_t = std::vector<packet_t>;

template<typename... Ts>
struct overloaded : Ts ... {
    using Ts::operator()...;
};
template<typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;

enum result_enum {
    e_wrong_order = 0, e_correct_order, e_equal_order
};

packet_t parse_line(const std::string &line) {
    packet_t packets;
    std::stack<packet_t *> ptr_stack;
    ptr_stack.push(&packets);

    for (int i = 0; i < line.size(); i++) {
        const char c = line[i];
        if (c == '[') {
            ptr_stack.push(&std::get<packet_t>(ptr_stack.top()->emplace_back(packet_t{})));
        } else if (c == ']') {
            ptr_stack.pop();
        } else if (c == ',') {

        } else {
            if (line[i + 1] == ',' || line[i + 1] == ']') {
                ptr_stack.top()->push_back(std::stoi(line.substr(i, 1)));
            } else if (line[i + 2] == ',' || line[i + 2] == ']') {
                ptr_stack.top()->push_back(std::stoi(line.substr(i, 2)));
                i++;
            }
        }
    }

    return packets;
}

result_enum compare_packets(const packet_t &a, const packet_t &b) {
    result_enum ret = e_equal_order;
    for (int i = 0; i < std::max(a.size(), b.size()) && ret == e_equal_order; ++i) {
        if (i == a.size()) {
            return e_correct_order;
        } else if (i == b.size()) {
            return e_wrong_order;
        } else {
            ret = std::visit(overloaded{
                    [](const packet_t &a, const packet_t &b) { return compare_packets(a, b); },
                    [](const packet_t &a, int b) { return compare_packets(a, {b}); },
                    [](int a, const packet_t &b) { return compare_packets({a}, b); },
                    [](int a, int b) {
                        if (a < b) {
                            return e_correct_order;
                        } else if (a > b) {
                            return e_wrong_order;
                        } else {
                            return e_equal_order;
                        }
                    }
            }, a[i], b[i]);
        }
    }

    return ret;
}

void run_2022_13(const std::vector<std::string> &input) {
    packets_t packets;
    for (const auto &line: input) {
        if (!line.empty()) {
            packets.push_back(parse_line(line));
        }
    }

    // Part 1
    int sum = 0;
    for (int i = 0; i < packets.size(); i += 2) {
        if (compare_packets(packets[i], packets[i + 1])) {
            sum += i / 2 + 1;
        }
    }
    std::cout << "part1: " << sum << std::endl;
}
