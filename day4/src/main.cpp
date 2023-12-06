#include <cmath>
#include <iostream>
#include <vector>
#include "utils.h"

using std::stoi;

const string input = "input";
const string test_input_A = "test";

int part_A(string input_file) {
    string content = utils::read_input(input_file);
    vector<string> lines = utils::get_lines(content); 
    vector<int> answers;

    for (string line : lines) {
        auto split_middle = utils::split(line, " | ");
        string left = split_middle[0];
        string right = split_middle[1];

        vector<string> left_values_str = utils::reg_match(left, "[0-9]+").strs;
        left_values_str.erase(left_values_str.begin()); // Remove first element (Card ID)
        vector<string> right_values_str = utils::reg_match(right, "[0-9]+").strs;

        int count = 0;

        for (string winning_num : left_values_str) {
            if (utils::vector_contains(right_values_str, winning_num)) {
                count += 1;
            }
        }

        if (count != 0) {
            int val = std::pow(2, count-1);
            answers.push_back(val);
        }
    }

    return utils::sum(answers);
}

void test_A() {
    int ans_A = part_A(test_input_A);

    cout << "(TEST A) " << ans_A << endl;
}

int main() {
    test_A();

    int ans = part_A(input);

    cout << "(A) " << ans << endl;
}
