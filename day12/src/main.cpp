#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "utils.h"

using std::string, std::vector, std::make_pair, std::map;
using llint = long long int;
using coord = std::pair<llint, llint>;

const string input = "input";
const string test = "test";

int sum_from_index_pone(vector<int> &vals, int index) {
    int sum = 0;
    for (int i = index; i < vals.size(); i++) {
        sum += vals[i] + 1;
    }

    return sum;
}

void print_string_at_range(string &text, int index, int range) {
    for (int i = 0; i < text.size(); i++) {
        if (i >= index && i <= index + range - 1) {
            cout << "*";
        } else {
            cout << text[i];
        }
    }
    cout << endl;
} 

int count_pounds(string text) {
    int sum = 0;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == '#') sum++;
    }

    return sum;
}

int rec_count(string &text, vector<int> &vals, int current_val_index, int i_start_str, int pounds_counted_tot) {
    int sum = 0;

    int text_str_size = text.size();

    int this_size = vals[current_val_index];

    for (int i = i_start_str; i < text.size() - sum_from_index_pone(vals, current_val_index+1); i++) {
        bool t = true;
        int pounds_counted = 0;
        for (int j = 0; j < this_size; j++) {
            if (i + j >= text_str_size) {
                t = false;
                break;
            }
            if (text[i+j] == '#') pounds_counted++;

            t *= (text[i+j] == '#' || text[i+j] == '?');
        }

        // Checking in front
        if (i+this_size < text_str_size) {
            bool can_be_empty = (text[i+this_size] == '.' || text[i+this_size] == '?');
            t *= can_be_empty;
        }

        // Checking behind
        if (i-1 >= 0) {
            bool can_be_empty = (text[i-1] == '.' || text[i-1] == '?');
            t *= can_be_empty;
        }

        if (current_val_index == vals.size() - 1 && t == true) {
            if (pounds_counted + pounds_counted_tot == count_pounds(text))
                sum+=1;
        }

        if (t && current_val_index != vals.size() - 1) {
            sum += rec_count(text, vals, current_val_index+1, i+this_size+1, pounds_counted + pounds_counted_tot);
        }
    }

    return sum;
}

int part_A(string input_file) {

    auto lines = utils::read_lines(input_file);
    
    int values = 0;

    for (string line : lines) {
        string linec = line;
        auto splitted = utils::split(linec, " ");
        string first_part = splitted[0];
        string second_part = splitted[1];
      
        vector<int> counts = utils::vec_str_to_int(utils::split(second_part, ","));

        int c = rec_count(first_part, counts, 0, 0, 0);
        cout << c << endl;

        values += c;
    }

    return values;
}

int main() {
    int v = part_A("input");
    cout << "value " << v << endl;
}
