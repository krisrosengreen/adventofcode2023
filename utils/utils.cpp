#include "utils.h"
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <vector>
#include <regex>

namespace utils {

std::string read_input(std::string input_text) {
    std::ifstream file(input_text);
    std::string content((std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));
    
    return content;
}

std::vector<std::string> get_lines(std::string &content) {
    std::vector<std::string> tokens;
    std::stringstream ss(content);
    std::string token;
    while (std::getline(ss, token, '\n')) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> read_lines(string input_text) {
    string content = read_input(input_text);
    return get_lines(content);
} 

vector<int> vec_str_to_int(vector<string> const& vec) {
    vector<int> a;
    for (auto val : vec) a.push_back(std::stoi(val));
    return a;
}

template <typename T>
void replace(std::string &str, const std::map<std::string, T> &el_map) {
    for (auto const& [key, val] : el_map) {
        size_t pos = str.find(key);

        if (pos != std::string::npos) {
            str.replace(pos, 1, std::to_string(val));
        }
    }
}

template <typename T>
void replaceAll_map(std::string &str, const std::map<std::string, T> &el_map) {
    for (auto const& [key, val] : el_map) {
        size_t pos = 0;
        while ((pos = str.find(key, pos)) != std::string::npos) {
            str.replace(pos, 1, std::to_string(val));
        }
    }
}

void replaceAll(std::string &str, std::string key, std::string val) {
    size_t pos = 0;
    while ((pos = str.find(key, pos)) != std::string::npos) {
        str.replace(pos, 1, val);
    }
}

std::vector<std::string> split(std::string &str, std::string del){
    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string token = str;
    while((pos = str.find(del)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + del.length());
    }

    tokens.push_back(str);

    return tokens;
}

void print_vector_int(std::vector<int> &vec) {
    std::cout << "Printing vector" << std::endl;
    for (int i = 0; i < vec.size(); i++) {
        std::cout << "Line " << i << ": " << vec[i] << std::endl;
    }
}

bool vector_contains(vector<string> &vec, string key) {
    return std::find(vec.begin(), vec.end(), key) != vec.end();
}
/*
 *
 * Trimming functions!
 *
 */

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

/*
 *
 * Some regex function
 *
 */

rmatch reg_match(string input, string pattern) {
    std::regex rx(pattern);

    vector<int> index_match;
    vector<string> string_match;

    for (auto it = std::sregex_iterator(input.begin(), input.end(), rx);
            it != std::sregex_iterator(); ++it) {
        std::smatch match = *it;
        string match_str = match.str();

        index_match.push_back(it->position());
        string_match.push_back(match_str);
    }

    rmatch req_match;
    req_match.indeces = index_match;
    req_match.strs = string_match;

    return req_match;
}

vector<string> reg_match_strs(string input, string pattern) {
    rmatch regm = reg_match(input, pattern);

    return regm.strs;
}

/*
 *
 * Minor testing stuff
 *
 */

}
