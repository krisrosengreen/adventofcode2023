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

    std::vector<std::string> split(std::string &str, std::string del);

    int sum(std::vector<int> &vals);

    template <typename T>
    void print_vector(std::vector<T> &vec);

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
}
