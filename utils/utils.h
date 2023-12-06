#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using std::cout, std::endl, std::string, std::vector;

namespace utils {

    std::string read_input(std::string input_text);

    std::vector<std::string> get_lines(std::string &content);

    template <typename T>
    void replace(std::string &str, const std::map<std::string, T> &el_map);

    template <typename T>
    void replaceAll_map(std::string &str, const std::map<std::string, T> &el_map);

    void replaceAll(std::string &str, std::string key, std::string val);

    std::vector<std::string> split(std::string &str, std::string del);

    int sum(std::vector<int> &vals);

    int prod(std::vector<int> &vals);

    bool vector_contains(vector<string> &vec, string key);

    void print_vector(std::vector<std::string> &vec);

    void print_vector_int(std::vector<int> &vec);

    /*
     *
     * Trimming functions
     *
     */

    static inline void ltrim(std::string &s);

    static inline void rtrim(std::string &s);
    
    static inline void trim(std::string &s);

    static inline std::string ltrim_copy(std::string s);

    static inline std::string rtrim_copy(std::string s);

    static inline std::string trim_copy(std::string s);

    /*
     *
     *
     * Some regex functions!
     *
     */

    struct rmatch {
        vector<int> indeces;
        vector<string> strs;
    };

    rmatch reg_match(string input, string pattern);
}
