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

string concatenate_string(string base, int count) {
    auto splitted = utils::split(base, " ");

    string base1 = splitted[0];
    string base2 = splitted[1];

    string base1_final = base1;
    string base2_final = base2;

    for (int i = 1; i < count; i++) {
        base1_final.append("?");
        base1_final.append(base1);

        base2_final.append(",");
        base2_final.append(base2);
    }

    base1_final.append(" ");
    base1_final.append(base2_final);

    return base1_final;
} 

string concatenate_string_front(string base) {
    auto splitted = utils::split(base, " ");

    string base1 = splitted[0];
    string base2 = splitted[1];

    base1.append("? ");
    base1.append(base2);

    return base1;
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

int poss_cfgs(string line) {
    string linec = line;
    auto splitted = utils::split(linec, " ");
    string first_part = splitted[0];
    string second_part = splitted[1];

    vector<int> counts = utils::vec_str_to_int(utils::split(second_part, ","));

    int c = rec_count(first_part, counts, 0, 0, 0);
    return c;
}

int part_A(string input_file) {

    auto lines = utils::read_lines(input_file);
    
    int values = 0;

    for (string line : lines) {
        values += poss_cfgs(line);
    }

    return values;
}

llint part_B(string input_file) {
    auto lines = utils::read_lines(input_file);
    llint values = 0;

    for (string line : lines) {
        cout <<"[LINE]" << endl;
        cout << line << endl;
        string line1 = line;

        string line3 = "?";
        line3.append(line1);

        string line2 = line1;
        line2 = concatenate_string_front(line2);

        string line5 = concatenate_string(line, 2);

        llint countbase = poss_cfgs(line1);

        llint count2 = poss_cfgs(line2);
        llint count3 = poss_cfgs(line3);
        llint c2prod = 1;
        llint c3prod = 1;

        for (int i = 0; i < 4; i++) {
            c2prod *= count2;
            c3prod *= count3;
        }

        llint finalval = c2prod*countbase;
        llint finalval2 = c3prod*countbase;
        cout << "FRO " << finalval << endl;
        cout << "END " << finalval2 << endl;
        cout << "count2 " << count2 << " count3 " << count3 << endl;
        values += finalval;
    }

    return values;
}

int main() {
    llint v = part_B("test");
    cout << "value " << v << endl;
}
