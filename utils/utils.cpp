#include "utils.h"
#include <sstream>
#include <fstream>

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

}
