#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>

class Formatter {
public:
    static std::string utf8_truncate(const std::string& str, size_t max_len) {
        std::string res;
        size_t count = 0;
        for (size_t i = 0; i < str.length(); ) {
            if (count >= max_len) { res += "..."; break; }
            unsigned char c = str[i];
            size_t len = (c >= 0xf0) ? 4 : (c >= 0xe0) ? 3 : (c >= 0xc0) ? 2 : 1;
            if (i + len > str.length()) break;
            res += str.substr(i, len);
            i += len; count++;
        }
        return res;
    }

    static void print_genmon(const std::string& icon, const std::string& txt, const std::string& tool) {
        if (txt.empty()) return;
        std::printf("<txt> %s %s </txt>\n", icon.c_str(), txt.c_str());
        std::printf("<tool>%s</tool>\n", tool.c_str());
        std::printf("<click>playerctl play-pause</click>\n");
    }
};

#endif
