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
using coord = std::pair<int, int>;

const string input = "input";
const string test = "test";

struct Galaxy {
    int x_inflate;
    int y_inflate;
};

void print_coord(coord& c) {
    cout << c.first << " " << c.second << endl;
}

int expand_universe(string input, int rate_expansion) {
    auto lines = utils::read_lines(input);

    map<coord, Galaxy> galaxies;

    // expand y-space
    int y_space_expansion = 0;
    for (int y = 0; y < lines.size(); y++) {
        int n_empty_space = 0;
        for (int x = 0; x < lines[0].size(); x++) {
            if (lines[y][x] == '.') n_empty_space++; 
            else if (lines[y][x] == '#') {
                coord pos = make_pair(x, y);
                galaxies[pos] = Galaxy {0, y_space_expansion};
            } 
        }

        if (n_empty_space == lines[0].size()) y_space_expansion+=rate_expansion;
    }

    // expand x-space
    int x_space_expansion = 0;
    for (int x = 0; x < lines[0].size(); x++) {
        int n_empty_space = 0;
        for (int y = 0; y < lines.size(); y++) {
            if (lines[y][x] == '.') n_empty_space++; 
            else if (lines[y][x] == '#') {
                coord pos = make_pair(x, y);
                galaxies[pos].x_inflate = x_space_expansion;
            } 
        }

        if (n_empty_space == lines.size()) x_space_expansion+=rate_expansion;
    }

    vector<coord> post_expansion_pos;

    for (auto const& [key, val] : galaxies) {
        post_expansion_pos.push_back(make_pair(key.first + val.x_inflate, key.second + val.y_inflate));
    }


    vector<int> smallest_distances;
    for (int i = 0; i < post_expansion_pos.size(); i++) {
        for (int j = i+1; j < post_expansion_pos.size(); j++) {
            if (i == j) continue;
            int distance = abs(post_expansion_pos[i].first - post_expansion_pos[j].first) + abs(post_expansion_pos[i].second - post_expansion_pos[j].second);
            smallest_distances.push_back(distance);
        }
    }

    return utils::sum(smallest_distances);
}

int part_A(string input) {
    return expand_universe(input, 1);
}

void test_A() {
    int val = part_A(input); 
    cout << "ans: " << val << endl;
}

void test_B() {
    // int val = part_B(test); 
    // cout << "ans: " << val << endl;
}

int main() {
    // int val = part_A(input);
    // cout << "(A) " << val << endl;
    test_A();
}
