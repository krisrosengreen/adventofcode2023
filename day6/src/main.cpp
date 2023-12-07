#include <iostream>
#include <cmath>
#include <string>
#include "utils.h"

using std::string, std::cout, std::endl;

const string input = "input";
const string test = "test";

int dist(int time_hold, int time_max) {
    return time_hold*time_max - time_hold*time_hold;
}

int min_time(int time_max, int dist_record) {
    int approx_time = std::ceil(time_max/2.0 - sqrt(time_max*time_max / 4.0 - dist_record));

    if (dist(approx_time, time_max) == dist_record) {
        approx_time++;
    }

    return approx_time;
}

int num_wins(int max_time, int win_distance) {
    return max_time - 2*min_time(max_time, win_distance) + 1;
}

vector<int> strvec_to_intvec(vector<string> const& vec) {
    vector<int> to;

    for (auto str : vec) {
        to.push_back(std::stoi(str));
    }
    
    return to;
}

int part_A(string input_file) {
    string content = utils::read_input(input_file);
    vector<string> lines = utils::get_lines(content);

    utils::rmatch a;

    vector<int> times = strvec_to_intvec(utils::reg_match(lines[0], "[0-9]+").strs);
    vector<int> distances = strvec_to_intvec(utils::reg_match(lines[1], "[0-9]+").strs);

    vector<int> num_poss;

    for (int i = 0; i < times.size(); i++) {
        num_poss.push_back(num_wins(times[i], distances[i]));
    }

    return utils::prod(num_poss);
}

int part_B(string input_file) {
    string content = utils::read_input(input_file);
    vector<string> lines = utils::get_lines(content);

    utils::rmatch a;

    vector<string> times_vec = utils::reg_match(lines[0], "[0-9]+").strs;
    vector<string> distances_vec = utils::reg_match(lines[1], "[0-9]+").strs;

    string times = "";
    string distances = "";

    for (auto time : times_vec) {
        times.append(time);
    }

    for (auto distance : distances_vec) {
        distances.append(distance);
    }

    unsigned long int distance_rec = std::stoul(distances);
    unsigned long int time_max = std::stoul(times);

    cout << "dist_rec: " << distance_rec << " time: " << time_max << endl;

    unsigned long int t;
    for (unsigned long int i = 0; i < time_max; i++) {
        t = i;
        int distance_my = dist(t, time_max);

        if (distance_my > distance_rec) {
            cout << "time " << t << endl;
            break;
        }
    }

    int wins = time_max - 2*t + 1;

    return wins;
}

void test_A() {
    int val = part_A(test);
    cout << "[TEST A] " << val << endl;
}

void test_B() {
    int val = part_B(test);
    cout << "[TEST B] " << val << endl;
}

void test_C() {
    int wins = num_wins(71530, 940200);
    cout << wins << endl;
}

int main() {
    // test_A();
    // test_B();
    test_C();

    // int ans_A = part_A(input);
    // cout << "(A) " << ans_A << endl;

    // int ans_B = part_B(input);
    // cout << "(B) " << ans_B << endl;
}
