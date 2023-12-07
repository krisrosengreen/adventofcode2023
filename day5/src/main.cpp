#include <iostream>
#include <map>
#include <string>
#include "utils.h"

using std::make_pair, std::pair, utils::rmatch, std::map;
using section_lines = vector<vector<string>>;
using vec_seed_dest = vector<pair<unsigned long int, unsigned long int>>;

const string input = "input";
const string test = "test";

vector<unsigned long int> str_map_ulint(vector<string> const& vec) {
    vector<unsigned long int> ret;
    for (auto str : vec) ret.push_back(std::stoul(str));

    return ret;
}

section_lines parse_map(vector<string> const& sections) {
    section_lines parsed_sections;

    for (auto section : sections) {
        vector<string> lines = utils::get_lines(section);

        //Pop the first line
        lines.erase(lines.begin());

        parsed_sections.push_back(lines);
    }

    return parsed_sections;
}

bool is_value_contained_line(string line, unsigned long int sec_source_val) {
    rmatch regm = utils::reg_match(line, "[0-9]+");

    unsigned long int drs = std::stoul(regm.strs[0]); // destination range start
    unsigned long int srs = std::stoul(regm.strs[1]); // destination range start
    unsigned long int rl = std::stoul(regm.strs[2]); // destination range start

    return sec_source_val >= srs && sec_source_val <= srs + rl - 1;
}

unsigned long int get_destination_value(string line, unsigned long int sec_source_val) {
    rmatch regm = utils::reg_match(line, "[0-9]+");

    unsigned long int drs = std::stoul(regm.strs[0]); // destination range start
    unsigned long int srs = std::stoul(regm.strs[1]); // destination range start

    unsigned long int diff = sec_source_val - srs;
    unsigned long int destination = drs + diff;

    // cout << "from " << sec_source_val << " to " << destination << endl;

    return destination;
}

unsigned long int rec_dim_conv(section_lines const& dim_conv, size_t current_sec, unsigned long int sec_source_val) {
    vector<string> lines = dim_conv[current_sec];

    unsigned long int dest_val = sec_source_val;

    for (string line : lines) {
        if (is_value_contained_line(line, sec_source_val)) {
            dest_val = get_destination_value(line, sec_source_val);
            break;
        }
    }

    if (dim_conv.size() - 1 == current_sec) {
        return dest_val;
    } else {
        return rec_dim_conv(dim_conv, current_sec+1, dest_val);
    }
}

unsigned long int part_A(string file_input) {
    string content = utils::read_input(file_input);
    auto double_nl_split = utils::split(content, "\n\n");
    rmatch regm = utils::reg_match(double_nl_split[0], "[0-9]+");
    vector<string> seeds_str = regm.strs;
    vector<unsigned long int> seeds = str_map_ulint(seeds_str);

    // Remove first section containing seeds from double_nl_split vector
    double_nl_split.erase(double_nl_split.begin());

    section_lines dim_conv = parse_map(double_nl_split);

    vec_seed_dest ans;

    for (unsigned long int seed : seeds) {
        // cout << "[SEED] " << seed << endl;
        unsigned long int dest = rec_dim_conv(dim_conv, 0, seed);
        ans.push_back(make_pair(seed, dest));
    }

    // cout << "Answers: " << endl;

    unsigned long int seed = 1000000000;
    unsigned long int loc = 10000000000;

    for (auto pair : ans) {
        // cout << pair.first << " -> " << pair.second << endl;
        
        if (pair.second < loc) {
            loc = pair.second;
            seed = pair.first;
        }
    }

    return loc;
}

unsigned long int part_B(string file_input) {
    string content = utils::read_input(file_input);
    auto double_nl_split = utils::split(content, "\n\n");
    rmatch regm = utils::reg_match(double_nl_split[0], "[0-9]+");
    vector<string> seeds_str = regm.strs;
    vector<unsigned long int> seeds = str_map_ulint(seeds_str);

    // Remove first section containing seeds from double_nl_split vector
    double_nl_split.erase(double_nl_split.begin());

    section_lines dim_conv = parse_map(double_nl_split);

    vec_seed_dest ans;

    for (int i = 0; i < seeds.size(); i+=2) {
        unsigned long int seed_start = seeds[i];

        for (unsigned long int next = 0; next < seeds[i+1] - 1; next++) {
            unsigned long int seed = seed_start + next;
            // cout << "[SEED] " << seed << endl;
            unsigned long int dest = rec_dim_conv(dim_conv, 0, seed);
            ans.push_back(make_pair(seed, dest));
        }
    }

    // cout << "Answers: " << endl;

    unsigned long int seed = 1000000000;
    unsigned long int loc = 10000000000;

    for (auto pair : ans) {
        // cout << pair.first << " -> " << pair.second << endl;
        
        if (pair.second < loc) {
            loc = pair.second;
            seed = pair.first;
        }
    }

    return loc;
}

void test_A() {
    unsigned long int ans = part_A(test);
    cout << "(TEST A) " << ans << endl;
}

void test_B() {
    unsigned long int ans = part_B(test);
    cout << "(TEST B) " << ans << endl;
}

int main() {
    test_A();
    test_B();
    unsigned long int ans = part_A(input);
    cout << "(A) " << ans << endl;

    unsigned long int ans_B = part_B(input);
    cout << "(B) " << ans_B << endl;
}
