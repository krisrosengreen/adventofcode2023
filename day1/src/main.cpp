#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "utils.h"

using std::string, std::cout, std::endl, std::vector;

const string input_text_A = "input";
const string input_text_test = "input_test";
const std::map<string, int> substr_val_pair = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

int part_A(string input_text) {

    string content = utils::read_input(input_text);
    auto lines = utils::get_lines(content);

    vector<int> values;

    for (string line : lines) {
        char start = '\0';
        char end = '\0';

        for (int i = 0; i < line.length(); i++) {
            char current_char = line.at(i);
            if (std::isdigit(line.at(i))) {
                if (start == '\0') {
                    start = current_char;
                    end = current_char;
                } else {
                    end = current_char;
                }
            }
        }

        int i_start = start - '0';
        int i_end = end - '0';

        int value = i_start*10 + i_end;
        values.push_back(value);
    }

    int sum = 0;
    for (int val : values) {
        sum += val;
    }

    return sum;
}


template <typename T>
string copy_digits(string &str, const std::map<string, T> &el_map) {
    string new_string(str.length(), ' ');

    for (auto const& [key, val] : el_map) {
        size_t pos = 0;
        while((pos = str.find(key, pos)) != string::npos) {
            new_string.replace(pos, 1, std::to_string(val));
            pos += 1;
        }
    }

    for (int i = 0; i < str.length(); i++) {
        if (std::isdigit(str.at(i))) {
            new_string.replace(i, 1, string(1, str.at(i)));
        }
    }

    return new_string;
}

std::vector<string> copy_vector_digits(std::vector<string> lines) {
    std::vector<string> new_vec;

    for (string line : lines) {
        new_vec.push_back(copy_digits(line, substr_val_pair));
    }

    return new_vec;
}

int part_B(string input_text) {
    string content = utils::read_input(input_text);
    auto raw_lines = utils::get_lines(content);
    auto lines = copy_vector_digits(raw_lines);

    vector<int> values;

    for (string line : lines) {
        char start = '\0';
        char end = '\0';

        for (int i = 0; i < line.length(); i++) {
            char current_char = line.at(i);
            if (std::isdigit(line.at(i))) {
                if (start == '\0') {
                    start = current_char;
                    end = current_char;
                } else {
                    end = current_char;
                }
            }
        }

        int i_start = start - '0';
        int i_end = end - '0';

        int value = i_start*10 + i_end;
        values.push_back(value);
    }

    int sum = 0;
    for (int val : values) {
        sum += val;
    }

    return sum;

}

void test() {
    cout << "(a) Test val: " << part_A(input_text_test) << " correct val: " << 324 << endl;
}

void test_B() {
    cout << "(b) Test val: " << part_B(input_text_test) << " correct val: " << 310 << endl;
}


void test_C() {
    cout << "(c) Test val: " << part_B("input_test_c") << " correct val: " << 281 << endl;

    string content = utils::read_input("input_test_c");
    auto raw_lines = utils::get_lines(content);
    auto lines = copy_vector_digits(raw_lines);

    cout << "[PART C]" << endl;
    for (auto line : lines) {
        cout << line << endl;
    }

    cout << "[END PART C]" << endl;
}

int main() {
    test();
    test_B();
    test_C();

    int ans = part_A(input_text_A);
    cout << "(A) Total found: " << ans << endl;

    int ans_b = part_B(input_text_A);
    cout << "(B) Total found: " << ans_b << endl;
}
