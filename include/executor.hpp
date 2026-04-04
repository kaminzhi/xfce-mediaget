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
        
        // Fix: Use explicit function pointer type to avoid attribute warnings
        std::unique_ptr<FILE, int(*)(FILE*)> pipe(popen(cmd.c_str(), "r"), pclose);
        
        if (!pipe) return "";
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        if (!result.empty() && result.back() == '\n') result.pop_back();
        return result;
    }
};

#endif
