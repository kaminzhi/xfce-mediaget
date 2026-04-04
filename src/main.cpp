#include <iostream>
#include "executor.hpp"
#include "formatter.hpp"
#include "player.hpp"

/*
std::string format_time(std::string micro_str) {
    if (micro_str.empty() || micro_str.find_first_not_of("0123456789") != std::string::npos) 
        return "00:00";
    try {
        long long total_seconds = std::abs(std::stoll(micro_str) / 1000000);
        // long long minutes = total_seconds / 60;
        long long seconds = total_seconds % 60;
        
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%02lld:%02lld", seconds / 60, seconds % 60);
        return std::string(buf);
    } catch (...) {
        return "00:00";
    }
}
*/


int main() {
    std::string status = Executor::run("playerctl status 2>/dev/null");
    if (status != "Playing" && status != "Paused") return 0;

    PlayerMetadata m;
    // m.status = status;
    m.artist = Executor::run("playerctl metadata xesam:artist 2>/dev/null");
    m.title  = Executor::run("playerctl metadata xesam:title 2>/dev/null");
    m.player = Executor::run("playerctl -l 2>/dev/null | head -n 1");
    m.art_url = Executor::run("playerctl metadata mpris:artUrl 2>/dev/null");

    // std::string pos = format_time(Executor::run("playerctl position 2>/dev/null"));
    // std::string len = format_time(Executor::run("playerctl metadata mpris:length 2>/dev/null"));
    // m.time = pos + " / " + len;

    // std::string icon = (status == "Playing") ? "󰐊" : "󰏤";
    
    Formatter::print_genmon(m);

    return 0;
}
