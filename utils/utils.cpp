#include "utils.h"
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <iostream>

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
void replaceAll(std::string &str, const std::map<std::string, T> &el_map) {
    for (auto const& [key, val] : el_map) {
        size_t pos = 0;
        while ((pos = str.find(key, pos)) != std::string::npos) {
            str.replace(pos, 1, std::to_string(val));
        }
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

void print_vector(std::vector<std::string> &vec) {
    std::cout << "Printing vector" << std::endl;
    for (int i = 0; i < vec.size(); i++) {
        std::cout << "Line " << i << ": " << vec[i] << std::endl;
    }
}

int sum(std::vector<int> &vals) {
    int sum = 0;

    for (int val : vals) {
        sum += val;
    }

    return sum;
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

}
