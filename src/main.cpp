#include <iostream>
#include <vector>
#include <unistd.h>
#include "executor.hpp"
#include "formatter.hpp"
#include "player.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    int width = 150;
    int height = 83;
    int opt;

    while ((opt = getopt(argc, argv, "w:h:")) != -1) {
        switch (opt) {
            case 'w': width = std::stoi(optarg); break;
            case 'h': height = std::stoi(optarg); break;
        }
    }
    
    std::string players_raw = Executor::run("playerctl -l 2>/dev/null");
    if (players_raw.empty()) {
        std::cout << "<txt> No Media Playing </txt>" << std::endl;
        return 0;
    }
    
    std::vector<std::string> players = Utils::split(players_raw, '\n');
    std::string target_player = "";

    for (const auto& p : players) {
        if (Executor::run("playerctl -p " + p + " status 2>/dev/null") == "Playing") {
            target_player = p;
            break;
        }
    }
    if (target_player.empty()) target_player = players[0];

    std::string status = Executor::run("playerctl -p " + target_player + " status 2>/dev/null");
    if (status != "Playing" && status != "Paused") return 0;

    PlayerMetadata m;
    // m.status = status;
    m.player = target_player;
    m.artist = Executor::run("playerctl -p " + target_player + " metadata xesam:artist 2>/dev/null");
    m.title  = Executor::run("playerctl -p " + target_player + " metadata xesam:title 2>/dev/null");
    
    std::string raw_url = Executor::run("playerctl -p " + target_player + " metadata mpris:artUrl 2>/dev/null");
    m.art_url = Executor::process_art(raw_url, width, height);
    
    // std::string pos = Utils::format_time(Executor::run("playerctl -p " + target_player + " position 2>/dev/null"));
    // std::string len = Utils::format_time(Executor::run("playerctl -p " + target_player + " metadata mpris:length 2>/dev/null"));
    // m.time = pos + " / " + len;

    Formatter::print_genmon(m);

    return 0;
}
