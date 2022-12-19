//
// Created by Maarten Peels on 06/12/2022.
//

#include <iostream>
#include <string>
#include <vector>

struct Bag {
    std::vector<char> contents;
    std::vector<char> contents_left;
    std::vector<char> contents_right;
    char duplicate {};
};

int get_priority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }
    return 0;
}

void remove_duplicates(std::vector<char> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }

    v.erase(end, v.end());
}


void run_2022_03(const std::vector<std::string>& input) {
    std::vector<Bag> bags;

    for (const auto& line : input) {
        Bag bag;
        bag.contents = std::vector<char>(line.begin(), line.end());
        bag.contents_left = std::vector<char>(line.begin(), line.begin() + line.size() / 2);
        bag.contents_right = std::vector<char>(line.begin() + line.size() / 2, line.end());

        for (int i = 0; i < bag.contents_left.size(); i++) {
            char c = bag.contents_left[i];
            if(std::find(bag.contents_right.begin(), bag.contents_right.end(), c) != bag.contents_right.end()) {
                bag.duplicate = c;
                break;
            }
        }

        bags.push_back(bag);
    }

    // Part 1
    int count_p1 = 0;
    for (const auto& bag : bags) {
        count_p1 += get_priority(bag.duplicate);
    }
    std::cout << "Part 1: " << count_p1 << std::endl;

    // Part 2
    int count_p2 = 0;
    std::vector<Bag> bags_p2;

    for (const auto& bag : bags) {
        Bag bag_p2 = bag; // copy
        remove_duplicates(bag_p2.contents);
        bags_p2.push_back(bag_p2);

        if (bags_p2.size() == 3) {
            for (int i = 0; i < bags_p2[0].contents.size(); i++) {
                char c = bags_p2[0].contents[i];
                if(std::find(bags_p2[1].contents.begin(), bags_p2[1].contents.end(), c) != bags_p2[1].contents.end()) {
                    if(std::find(bags_p2[2].contents.begin(), bags_p2[2].contents.end(), c) != bags_p2[2].contents.end()) {
                        count_p2 += get_priority(c);
                    }
                }
            }

            bags_p2.clear();
        }
    }
    std::cout << "Part 2: " << count_p2 << std::endl;
}
