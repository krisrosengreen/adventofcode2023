#include <string>
#include <vector>
#include <map>

namespace utils {

std::string read_input(std::string input_text);

std::vector<std::string> get_lines(std::string &content);

template <typename T>
void replace(std::string &str, const std::map<std::string, T> &el_map);

template <typename T>
void replaceAll(std::string &str, const std::map<std::string, T> &el_map);
}
