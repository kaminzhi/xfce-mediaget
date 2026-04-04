#include <iostream>
#include "executor.hpp"
#include "formatter.hpp"

int main() {
    std::string status = Executor::run("playerctl status 2>/dev/null");
    if (status != "Playing" && status != "Paused") return 0;

    std::string artist = Executor::run("playerctl metadata artist 2>/dev/null");
    std::string title = Executor::run("playerctl metadata title 2>/dev/null");
    
    if (title.empty()) return 0;

    std::string icon = (status == "Playing") ? "󰐊" : "󰏤";
    std::string full = artist.empty() ? title : artist + " - " + title;
    std::string short_txt = Formatter::utf8_truncate(full, 25);

    Formatter::print_genmon(icon, short_txt, full);

    return 0;
}
