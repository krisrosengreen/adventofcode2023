#include <cmath>
#include <iostream>
#include <vector>
#include "utils.h"

const string input = "input";
const string test_input_A = "test";

int line_points(string line) {
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

    return count;
}

class rec_B {
    public:
        std::map<int, int> values;
        int rec_points(vector<string> &lines, int current_index) {
            std::map<int, int>::iterator iter = values.find(current_index);
            if (iter != values.end()) {
                return iter->second;
            }

            int points_sum = 0;
            int this_points = line_points(lines[current_index]);
            points_sum += this_points;

            for (int i = current_index + 1; i < current_index + this_points + 1; i++) {
                points_sum += rec_points(lines, i);
            }

            return values[current_index] = points_sum;
        }
};


int part_B(string input_file) {
    string content = utils::read_input(input_file);
    vector<string> lines = utils::get_lines(content); 

    int sum_points = 0;

    rec_B rec;

    for (int i = 0; i < lines.size(); i++) {
        sum_points++; 
        sum_points += rec.rec_points(lines, i);
    }

    return sum_points;
}

int part_A(string input_file) {
    string content = utils::read_input(input_file);
    vector<string> lines = utils::get_lines(content); 
    vector<int> answers;

    for (int line_index = 0; line_index < lines.size(); line_index++) {
        string line = lines[line_index];
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

void test_B() {
    int ans_B = part_B(test_input_A);
    cout << "(TEST B) " << ans_B << endl;
}

void test_C() {
    int ans_B = part_B("test2");
    cout << "(TEST C) " << ans_B << endl;
}

int main() {
    test_A();
    test_B();
    test_C();
   
    int ans = part_A(input);
    cout << "(A) " << ans << endl;

    int ans_b = part_B(input);
    cout << "(B) " << ans_b << endl;
}
