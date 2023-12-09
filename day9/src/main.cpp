#include <iostream>
#include <vector>
#include <string>
#include "utils.h"

using std::string, std::vector;
using llint = long long int;

const string input = "input";
const string test = "test";

struct Diffs {
    llint lower_row_predict;
};

vector<llint> differences(vector<llint> const& vec) {
    vector<llint> a;
    for (int i = 0; i < vec.size()-1; i++) {
        a.push_back(vec[i+1]-vec[i]);
    }
    return a;
}

vector<llint> get_values(string line) {
    vector<string> vals_str = utils::reg_match_strs(line, "-?\\w+");
    vector<llint> vals;

    for (auto str : vals_str) {
        vals.push_back(std::stoll(str));
    }

    return vals;
}

Diffs rec_sequence_pred(vector<llint> sequence) {
    if (utils::sum(sequence) == 0) {
        return Diffs{0};
    } else {
        Diffs ds = rec_sequence_pred(differences(sequence));
        int diff = sequence.back() + ds.lower_row_predict;
        ds.lower_row_predict = diff;

        return ds;
    }
}

Diffs rec_sequence_pred_back(vector<llint> sequence) {
    if (utils::sum(sequence) == 0) {
        return Diffs{0};
    } else {
        Diffs ds = rec_sequence_pred_back(differences(sequence));
        int diff = sequence[0] - ds.lower_row_predict;
        ds.lower_row_predict = diff;

        return ds;
    }
}

int part_A(string input_file) {
    auto lines = utils::read_lines(input_file);

    llint sum = 0;

    for (string line : lines) {
        vector<llint> sequence = get_values(line);
        Diffs ds = rec_sequence_pred(sequence);

        sum += ds.lower_row_predict;
    }
    
    return sum;
}

int part_B(string input_file) {
    auto lines = utils::read_lines(input_file);

    llint sum = 0;

    for (string line : lines) {
        vector<llint> sequence = get_values(line);
        Diffs ds = rec_sequence_pred_back(sequence);

        sum += ds.lower_row_predict;
    }
    
    return sum;
}

int main() {
    llint val = part_A(input);
    cout << "(a) ans " << val << endl;

    llint val_B = part_B(input);
    cout << "(b) ans " << val_B << endl;
}
