//
// Created by Siqing Zhang on 19/2/2023.
//
#include <iostream>

void srt2(auto &x, auto &y) {
    if (x > y) {
        std::swap(x, y);
    }
}

void srt3(auto &a, auto &b, auto &c)requires
std::is_same_v<std::remove_cvref_t<decltype(a)>, std::remove_cvref_t<decltype(b)>> &&
std::is_same_v<std::remove_cvref_t<decltype(b)>, std::remove_cvref_t<decltype(c)>> {
    if (srt2(a, b);b < c) return;
    if (std::swap(b, c);a < b) return;
    std::swap(a, b);
}

auto sort3(int &a, int &b, int &c) -> void {
    srt3(a, b, c);
}

auto sort3(std::string &a, std::string &b, std::string &c) -> void {
    srt3(a, b, c);
}