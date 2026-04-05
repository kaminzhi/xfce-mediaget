#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>
#include <cmath>

class Utils {
public:
    /*
    static std::string format_time(std::string micro_str) {
        if (micro_str.empty() || micro_str.find_first_not_of("-0123456789") != std::string::npos) 
            return "00:00";
        try {
            long long total_seconds = std::abs(std::stoll(micro_str) / 1000000);
            long long minutes = total_seconds / 60;
            long long seconds = total_seconds % 60;

            char buf[32];
            std::snprintf(buf, sizeof(buf), "%02lld:%02lld", minutes, seconds);
            return std::string(buf);
        } catch (...) {
            return "00:00";
        }
    }
    */

    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            if (!token.empty()) tokens.push_back(token);
        }
        return tokens;
    }
};

#endif
