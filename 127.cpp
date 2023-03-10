//
// Created by Siqing Zhang on 20/2/2023.
//
#include <iostream>
#include <string>
using namespace std;


struct AStar {
    static constexpr int getH(const string& status, const string& target) {
        int ret = 0;
        for (int i = 0; i < 4; ++i) {
            int dist = abs(int(status[i]) - int(target[i]));
            ret += min(dist, 26 - dist);
        }
        return ret;
    };

    AStar(const string& status, const string& target, int g): status_{status}, g_{g}, h_{getH(status, target)} {
        f_ = g_ + h_;
    }

    bool operator< (const AStar& that) const {
        return f_ > that.f_;
    }

    string status_;
    int f_, g_, h_;
};


class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unsigned len = beginWord.size();

    }
};