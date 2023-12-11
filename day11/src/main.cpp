#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include "utils.h"

using std::string, std::vector, std::make_pair, std::map;
using llint = long long int;
using coord = std::pair<llint, llint>;

const string input = "input";
const string test = "test";

struct Galaxy {
    llint x_inflate;
    llint y_inflate;
};

void print_coord(coord& c) {
    cout << c.first << " " << c.second << endl;
}

llint expand_universe(string input, llint rate_expansion) {
    rate_expansion--; // One row expansion is already counted for in code below
    auto lines = utils::read_lines(input);

    map<coord, Galaxy> galaxies;

    // expand y-space
    llint y_space_expansion = 0;
    for (int y = 0; y < lines.size(); y++) {
        int n_empty_space = 0;
        for (int x = 0; x < lines[0].size(); x++) {
            if (lines[y][x] == '.') n_empty_space++; 
            else if (lines[y][x] == '#') {
                coord pos = make_pair(x, y);
                galaxies[pos] = Galaxy {0, y_space_expansion};
            } 
        }

        if (n_empty_space == lines[0].size()) y_space_expansion += rate_expansion;
    }

    vector<coord> post_expansion_pos;

    // expand x-space
    llint x_space_expansion = 0;
    for (int x = 0; x < lines[0].size(); x++) {
        int n_empty_space = 0;
        for (int y = 0; y < lines.size(); y++) {
            if (lines[y][x] == '.') n_empty_space++; 
            else if (lines[y][x] == '#') {
                coord pos = make_pair(x, y);
                galaxies[pos].x_inflate = x_space_expansion;
                post_expansion_pos.push_back({pos.first + x_space_expansion, pos.second + galaxies[pos].y_inflate});
            } 
        }

        if (n_empty_space == lines.size()) x_space_expansion += rate_expansion;
    }

    vector<llint> smallest_distances;
    for (int i = 0; i < post_expansion_pos.size()-1; i++) {
        for (int j = i+1; j < post_expansion_pos.size(); j++) {
            llint distance = llabs(post_expansion_pos[i].first - post_expansion_pos[j].first) + llabs(post_expansion_pos[i].second - post_expansion_pos[j].second);
            smallest_distances.push_back(distance);
        }
    }

    return utils::sum(smallest_distances);
}

int part_A(string input) {
    return expand_universe(input, 2); // Empty rows are doubled
}

llint part_B(string input) {
    return expand_universe(input, 1000000); // Emptry rows a re multiplied by a million
}

void test_A() {
    int val = part_A(input); 
    cout << "[test A] ans: " << val << endl;
}

void test_B() {
    int val_a = expand_universe(test, 2);
    cout << "[test B1] ans: " << val_a << endl;

    int val = expand_universe(test, 10);
    cout << "[test B2] ans: " << val << endl;

    llint val_b = expand_universe(test, 100);
    cout << "[test B3] ans: " << val_b << endl;
}

int main() {
    test_A();

    test_B();
    int val = part_A(input);
    cout << "[PART A] " << val << endl;

    llint ans_b = expand_universe(input, 1000000);
    cout << "[PART B] " << ans_b << endl;
}
