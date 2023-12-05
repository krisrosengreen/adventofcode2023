#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

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

string read_input(string input_text) {
    std::ifstream file(input_text);
    std::string content((std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));
    
    return content;
}

vector<string> get_lines(string input_text, string &content) {
    std::vector<string> tokens;
    std::stringstream ss(content);
    std::string token;
    while (std::getline(ss, token, '\n')) {
        tokens.push_back(token);
    }

    return tokens;
}

int part_A(string input_text) {

    string content = read_input(input_text);
    auto lines = get_lines(input_text, content);

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

template <typename replacer>
void replace(string &str, const std::map<string, replacer> &el_map) {
    for (auto const& [key, val] : el_map) {
        size_t pos = str.find(key);

        if (pos != string::npos) {
            str.replace(pos, key.length(), std::to_string(val));
        }
    }
}

template <typename replacer>
void replaceAll(string &str, const std::map<string, replacer> &el_map) {
    for (auto const& [key, val] : el_map) {
        size_t pos = 0;
        while ((pos = str.find(key, pos)) != string::npos) {
            str.replace(pos, key.length(), std::to_string(val));
        }
    }
}

int part_B(string input_text) {
    string content = read_input(input_text);

    // Replace all number words to numbers
    replaceAll<int>(content, substr_val_pair);
    auto lines = get_lines(input_text, content);

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
    cout << "(b) Test val: " << part_B("input_test_c") << " correct val: " << 281 << endl;
}

int main() {
    test();
    test_B();
    test_C();

    string ts = "There once was a one small man two called Ben";

    replaceAll<int>(ts, substr_val_pair);

    cout << ts << endl;

    int ans = part_A(input_text_A);
    cout << "(A) Total found: " << ans << endl;

    int ans_b = part_B(input_text_A);
    cout << "(B) Total found: " << ans_b << endl;
}
