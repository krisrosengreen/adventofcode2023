#include <iostream>
#include <vector>
#include <map>
#include "utils.h"

using utils::rmatch;

const string input_test_A = "test";
const string input = "input";

bool has_row_up(int current_i, int row_length, int str_size) {
    return current_i >= row_length;
}

bool has_row_down(int current_i, int row_length, int str_size) {
    return current_i + row_length < str_size;
}

int current_row_max_i(int current_i, int row_length) {
    
}

int current_row_min_i(int current_i, int row_length) {
    
}

int part_A(string input) {
    string content = utils::read_input(input);
    vector<string> lines = utils::get_lines(content);
    int length = lines[0].length();
    rmatch regm = utils::reg_match(content, "[0-9]+");

    string contentraw = content;

    utils::replaceAll(contentraw, "\n", "");

    for (int i = 0; i < regm.indeces.size(); i++) {
        cout << regm.indeces[i] << " " << regm.strs[i] << endl;
    }

    return 0;
}

void test_A() {
    int ans_A = part_A(input_test_A);

    cout << "(TEST A) " << ans_A << endl;
}

int main() {
    test_A(); 
}
