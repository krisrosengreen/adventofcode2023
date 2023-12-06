#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utils.h"

using utils::rmatch, std::min, std::max;

const string input_test_A = "test";
const string input = "input";

vector<vector<int>> symbol_indeces(vector<string> &lines) {
    string symbol_pattern = "[^0-9.]";

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

int part_A(string input) {
    string content = utils::read_input(input);
    vector<string> lines = utils::get_lines(content);
    int length = lines[0].length();

    vector<vector<int>> symbol_line_is = symbol_indeces(lines);

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

    cout << "Values found: " << endl;
    utils::print_vector_int(answer_vals);

    return utils::sum(answer_vals);
}

void test_A() {
    int test_ans_A = part_A(input_test_A);

    cout << "(TEST A) " << test_ans_A << endl;
}

int main() {
    test_A(); 

    int ans_A = part_A(input);

    cout << "(A) " << ans_A << endl;
}
