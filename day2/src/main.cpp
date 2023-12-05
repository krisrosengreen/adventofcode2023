#include <iostream>
#include "utils.h"
#include <string>
#include <vector>
#include <map>

using std::string, std::map, std::vector, std::cout, std::endl;

const string input_A = "input";

void print_vector(std::vector<std::string> vec) {
    std::cout << "Printing vector" << std::endl;
    for (int i = 0; i < vec.size(); i++) {
        std::cout << "Line " << i << ": " << vec[i] << std::endl;
    }
}

void p(int val) {
    cout << val << endl;
}

int part_A(string input_file) {
    string content = utils::read_input(input_file);
    vector<string> lines = utils::get_lines(content);

    vector<int> ids;

    for (string line : lines) {
        vector<string> id_cubes = utils::split(line, ": ");
        string id_str = id_cubes[0];
        
        int id = std::stoi(utils::split(id_str, " ")[1]);
        
        string cubes = id_cubes[1];
        
        vector<string> games = utils::split(cubes, "; ");
        
        bool is_okay = true;
        
        for (string game : games) {
            vector<string> cubes = utils::split(game, ", ");

            for (string cube : cubes) {
                if (!is_okay) break;
                 vector<string> count_color = utils::split(cube, " ");
                 int count = std::stoi(count_color[0]);
                 string color = count_color[1];

                 if (color == "green") {
                    if (count > 13) is_okay = false;
                 } else if (color == "red") {
                    if (count > 12) is_okay = false;
                 } else if (color == "blue") {
                    if (count > 14) is_okay = false;
                 }
            }
        }

        if (is_okay) {
            ids.push_back(id);
        }
    }

    return utils::sum(ids);
}

void some_testing_strings() {
    string teststr = "asdasd asddasda";
    auto lines = utils::split(teststr, " ");

    for (auto line : lines) {
        cout << "line: " << line << endl;
    }
}

void test_input() {
    int ans = part_A("test");
    cout << "Test val: " << ans << " should be: " << 8 << endl;
}

int main() {
    test_input();

    int ans = part_A(input_A);

    cout << "Answer: " << ans << endl;
}
