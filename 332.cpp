//
// Created by Siqing Zhang on 16/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map<string,priority_queue<string,vector<string>,greater<string>>> out2;
    vector<string> output;
public:
    void travel(const string& departure){
        while (out2.count(departure) && !out2[departure].empty()){
            string nextStop = out2[departure].top();
            out2[departure].pop();
            travel(nextStop);
        }
        output.emplace_back(departure);
    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& ticket : tickets) {
            out2[ticket[0]].emplace(ticket[1]);
        }

        travel("JFK");

        reverse(output.begin(), output.end());
        return output;
    }
};