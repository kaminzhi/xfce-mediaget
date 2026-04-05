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

    static std::string process_art(const std::string& url, int w, int h) {
        if (url.empty()) return "";
        
        std::string raw_path = "/tmp/xfce-mediaget-raw";
        std::string thumb_path = "/tmp/xfce-mediaget-thumb.png";

        std::string download_cmd;
        if (url.find("http") == 0) {
            download_cmd = "curl -s -L -o " + raw_path + " \"" + url + "\"";
        } else {
            std::string clean_url = url;
            if (clean_url.find("file://") == 0) clean_url.erase(0, 7);
            download_cmd = "cp \"" + clean_url + "\" " + raw_path;
        }
        if (std::system(download_cmd.c_str()) != 0) return "";

        // -i: file_path
        // -vf scale=-1:24
        std::string size_str = std::to_string(w) + ":" + std::to_string(h);
        std::string resize_cmd = "ffmpeg -y -v quiet -i " + raw_path + 
                                " -vf \"scale=" + size_str + ":force_original_aspect_ratio=increase,crop=" + size_str + ",setsar=1\" " + 
                                thumb_path;
        std::system(resize_cmd.c_str());

        return thumb_path;
    }
};

#endif
