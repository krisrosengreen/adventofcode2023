#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include "utils.h"

using std::string, std::vector;

const string input = "input";
const string test = "test";

struct Node {
    vector<string> paths;
};

std::pair<string, Node> parse_line(string line) {
        auto tags = utils::reg_match_strs(line, "\\w+");

        string node_name = tags[0];
        string node_left = tags[1];
        string node_right = tags[2];

        return std::make_pair(node_name, Node{vector<string>{node_left, node_right}});
}

std::unordered_map<string, Node> parse_nodes(string nodes) {
    vector<string> lines = utils::get_lines(nodes);
    std::unordered_map<string, Node> nodes_map;

    for (auto line : lines) {
        auto [node_name, node] = parse_line(line);
        nodes_map[node_name] = node;
    }

    return nodes_map;
}

int part_A(string input_file) {
    string content = utils::read_input(input_file);

    vector<string> instrs_nodes = utils::split(content, "\n\n");

    string path_str = instrs_nodes[0];
    string nodes_str = instrs_nodes[1];

    vector<int> instrs;
    for (int i = 0; i < path_str.size(); i++) {
        if (path_str[i] == 'L') instrs.push_back(0);
        else instrs.push_back(1);
    }

    std::unordered_map<string, Node> nodes = parse_nodes(nodes_str);
    string node_start = parse_line(utils::get_lines(nodes_str)[0]).first;

    // string current_station = node_start;
    string current_station = "AAA";
    int steps = 0;

    while (current_station != "ZZZ") {
        int instr = instrs[steps % instrs.size()];
        cout << current_station << " " << steps << " "<< instr << endl; 
        current_station = nodes[current_station].paths[instr];
        steps++;
    }

    return steps;
}

bool all_at_Z(vector<string> const& stations) {
    for (auto str : stations) {
        if (str[2] != 'Z') return false;
    }
    return true;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

unsigned long int part_B(string input_file) {
    string content = utils::read_input(input_file);

    vector<string> instrs_nodes = utils::split(content, "\n\n");

    string path_str = instrs_nodes[0];
    string nodes_str = instrs_nodes[1];

    vector<int> instrs;
    for (int i = 0; i < path_str.size(); i++) {
        if (path_str[i] == 'L') instrs.push_back(0);
        else instrs.push_back(1);
    }

    std::unordered_map<string, Node> nodes = parse_nodes(nodes_str);

    // string current_station = node_start;
    vector<string> starting_stations;

    for (auto const& [key, val] : nodes) {
        if (key[2] == 'A') {
            starting_stations.push_back(key);
        }
    }

    utils::print_vector(starting_stations);

    vector<std::pair<int, int>> cycles_steps; // first is to enter cycle, second to repeat it

    for (int crawl_i = 0; crawl_i < starting_stations.size(); crawl_i++) {
        int steps = 0;

        string current_station = starting_stations[crawl_i];

        int steps_first_station = 0;
        int steps_cycle;

        while (true) {
            while (current_station[2] != 'Z' or steps == 0 or steps == steps_first_station) {
                //cout << steps << " " << current_station << endl;
                steps++;
                current_station = nodes[current_station].paths[instrs[(steps-1) % instrs.size()]];
            }

            cout << "  -> " << current_station << endl;

            if (steps_first_station == 0) { // Hasnt hit first station yet
                steps_first_station = steps;
            } else {
                steps_cycle = steps - steps_first_station;
                break;
            }
        }
    
        cout << starting_stations[crawl_i] << " " << steps_first_station << " " << steps_cycle << endl;

        cycles_steps.push_back({steps_first_station, steps_cycle});
    }

    unsigned long int current = cycles_steps[0].first;

    for (int i = 1; i < cycles_steps.size(); i++){
        unsigned long int next = cycles_steps[i].first;
        current = utils::lcm(current, next);
    }

    return current;
}

void test_A() {
    auto val = part_A(test);
    cout << "[test A] number of steps: " << val << endl;
}

void test_B() {
    auto val = part_B("test2");
    cout << "[test B] number of steps: " << val << endl;
}

int main() {
    // test_A(); 
    // test_B(); 

    // AUTO VAL_A = PART_A(INPUT);
    // cout << "(A) number of steps: " << val_A << endl;

    auto val_b = part_B(input);
    cout << "(B) number of steps: " << val_b << endl;
}
