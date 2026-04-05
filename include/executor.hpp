#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <memory>
#include <array>
#include <cstdio>

class Executor {
public:
    static std::string run(const std::string& cmd) {
        std::array<char, 128> buffer;
        std::string result;
        
        std::unique_ptr<FILE, int(*)(FILE*)> pipe(popen(cmd.c_str(), "r"), pclose);
        
        if (!pipe) return "";
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        if (!result.empty() && result.back() == '\n') result.pop_back();
        return result;
    }

    static std::string download_art(const std::string& url) {
        if (url.empty()) return "";
        if (url.find("http") != 0) return url;

        std::string tmp_path = "/tmp/xfce-mediaget-cover.jpg";
        std::string cmd = "curl -s -o " + tmp_path + " \"" + url + "\"";
        system(cmd.c_str());
        return tmp_path;
    }
};

#endif
