#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include "utils.h"

using utils::rmatch, std::min, std::max, std::map, std::pair;

const string input_test_A = "test";
const string input = "input";

vector<vector<int>> symbol_indeces(vector<string> &lines, string symbol_pattern) {
    vector<vector<int>> lines_indeces;

    for (string line : lines) {
        rmatch symbols = utils::reg_match(line, symbol_pattern);

        lines_indeces.push_back(symbols.indeces);
    }

    return lines_indeces;
}

bool vector_has_value(vector<int> &vec, int val) {
    return std::find(vec.begin(), vec.end(), val) != vec.end();
}

bool contains_symbols(vector<vector<int>> &line_indeces, int line_index, int begin, int end) {
    for (int i = begin; i < end; i++) {
        if (vector_has_value(line_indeces[line_index], i)) {
            return true;
        }
    } 

    return false;
}

int get_symbol_index(vector<vector<int>> &line_indeces, int line_index, int begin, int end) {
    for (int i = begin; i < end; i++) {
        if (vector_has_value(line_indeces[line_index], i)) {
            return i;
        }
    } 

    return false;
}

bool contains_symbols_around_number(vector<vector<int>> &line_indeces, int line_index, int w_begin, int w_end) {
    // Check above
    if (line_index != 0) {
        if (contains_symbols(line_indeces, line_index - 1, w_begin - 1, w_end + 1)) {
            return true;
        }
    }

    // Check same line - symbol index before and after word
    if (vector_has_value(line_indeces[line_index], w_begin - 1) || vector_has_value(line_indeces[line_index], w_end)) {
        return true;
    }

    // Check below
    if (line_index <= line_indeces.size()) {
        if (contains_symbols(line_indeces, line_index + 1, w_begin - 1, w_end + 1)) {
            return true;
        }
    }

    return false;
}

std::pair<int, int> get_symbols_around_number(vector<vector<int>> &line_indeces, int line_index, int w_begin, int w_end) {
    // Check above
    if (line_index != 0) {
        if (contains_symbols(line_indeces, line_index - 1, w_begin - 1, w_end + 1)) {
            return pair<int, int>(line_index - 1, get_symbol_index(line_indeces, line_index - 1, w_begin - 1, w_end + 1));
        }
    }

    // Check same line - symbol index before and after word
    if (vector_has_value(line_indeces[line_index], w_begin - 1)) {
        return pair<int, int>(line_index, w_begin - 1);
    }

    if (vector_has_value(line_indeces[line_index], w_end)) {
        return pair<int, int>(line_index, w_end);
    }

    // Check below
    if (line_index <= line_indeces.size()) {
        if (contains_symbols(line_indeces, line_index + 1, w_begin - 1, w_end + 1)) {
            return pair<int, int>(line_index + 1, get_symbol_index(line_indeces, line_index + 1, w_begin - 1, w_end + 1));
        }
    }

    return std::pair<int, int>(-1,-1);
}

int part_A(string input) {
    string content = utils::read_input(input);
    vector<string> lines = utils::get_lines(content);
    int length = lines[0].length();

    vector<vector<int>> symbol_line_is = symbol_indeces(lines, "[^0-9.]");

    vector<int> answer_vals;
    
    for (int line_index = 0; line_index < lines.size(); line_index++) {
        string line = lines[line_index];
        rmatch regm = utils::reg_match(line, "[0-9]+");

        for (int line_num_index = 0; line_num_index < regm.indeces.size(); line_num_index++) {
            int num_length = regm.strs[line_num_index].size();
            int num_index_start = regm.indeces[line_num_index];

            if (contains_symbols_around_number(symbol_line_is, line_index, num_index_start, num_index_start + num_length)) {
                answer_vals.push_back(std::stoi(regm.strs[line_num_index]));
            }
        }
    }

    return utils::sum(answer_vals);
}

void q(int val) {
    cout << val << endl;
}

int part_B(string input) {
    string content = utils::read_input(input);
    vector<string> lines = utils::get_lines(content);
    int length = lines[0].length();

    q(1);
    vector<vector<int>> symbol_line_is = symbol_indeces(lines, "\\*");
    q(2);
    map<pair<int, int>, vector<int>> vals_around_gears;
    
    for (int line_index = 0; line_index < lines.size(); line_index++) {
        string line = lines[line_index];
        rmatch regm = utils::reg_match(line, "[0-9]+");

        for (int line_num_index = 0; line_num_index < regm.indeces.size(); line_num_index++) {
            int num_length = regm.strs[line_num_index].size();
            int num_index_start = regm.indeces[line_num_index];

            if (contains_symbols_around_number(symbol_line_is, line_index, num_index_start, num_index_start + num_length)) {
                pair<int, int> gear_pos = get_symbols_around_number(symbol_line_is, line_index, num_index_start, num_index_start + num_length);
                int number = std::stoi(regm.strs[line_num_index]);

                if (vals_around_gears.count(gear_pos)) {
                    vals_around_gears[gear_pos].push_back(number);
                } else {
                    vector<int> number_around_gear;
                    number_around_gear.push_back(number);

                    vals_around_gears[gear_pos] = number_around_gear;
                }
            }
        }
    }

    vector<int> answer_vals;

    // Gear values have to be multiplied together
    for (auto it = vals_around_gears.begin(); it != vals_around_gears.end(); it++) {
        if (it->second.size() == 2) {
            answer_vals.push_back(utils::prod(it->second));
        }
    }

    return utils::sum(answer_vals);
}

void test_A() {
    int test_ans_A = part_A(input_test_A);

    cout << "(TEST A) " << test_ans_A << endl;
}

void test_B() {
    int test_ans_B = part_B(input_test_A);

    cout << "(TEST B) " << test_ans_B << endl;
}

int main() {
    test_A(); 
    test_B();

    int ans_A = part_A(input);
    cout << "(A) " << ans_A << endl;

    int ans_B = part_B(input);
    cout << "(B) " << ans_B << endl;
}
