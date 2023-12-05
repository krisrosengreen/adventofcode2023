#include "utils.h"

std::string read_input(std::string input_text) {
    std::ifstream file(input_text);
    std::string content((std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));
    
    return content;
}

std::vector<std::string> get_lines(std::string input_text, std::string &content) {
    std::vector<std::string> tokens;
    std::stringstream ss(content);
    std::string token;
    while (std::getline(ss, token, '\n')) {
        tokens.push_back(token);
    }

    return tokens;
}
