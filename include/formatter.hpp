#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <sstream>
#include <iostream>
#include "player.hpp"

class Formatter {
public:
    static std::string utf8_truncate(const std::string& str, size_t max_len) {
        std::string res;
        size_t count = 0;
        for (size_t i = 0; i < str.length(); ) {
            if (count >= max_len) { res += ".."; break; }
            unsigned char c = (unsigned char)str[i];
            size_t len = (c >= 0xf0) ? 4 : (c >= 0xe0) ? 3 : (c >= 0xc0) ? 2 : 1;
            if (i + len > str.length()) break;
            res += str.substr(i, len);
            i += len; count++;
        }
        return res;
    }

    static void print_genmon(const PlayerMetadata& m) {
        std::string img_path = m.art_url;
        if (img_path.find("file://") == 0) img_path.erase(0, 7);

        if (!img_path.empty()) {
            std::cout << "<img>" << img_path << "</img>" << std::endl;
        }

        std::cout << "<txt> " << " " << utf8_truncate(m.title, 20) << " </txt>" << std::endl;

        std::stringstream ss;
        ss << "Artist: " << m.artist << "\n"
           << "Title:  " << m.title << "\n"
           << "Source: " << m.player << "\n" ;
        //   << "Time:   " << m.time;
        
        std::cout << "<tool>" << ss.str() << "</tool>" << std::endl;
        std::cout << "<click>playerctl play-pause</click>" << std::endl;
    }
};

#endif
