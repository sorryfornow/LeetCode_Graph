//
// Created by Siqing Zhang on 16/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> outD (n+1,0);
        vector<int> inD (n+1,0);

        for (auto& pair: trust){
            inD[pair[1]]++;
            outD[pair[0]]++;
        }
        for (int i = 1; i < n+1; ++i) {
            if (outD[i] == 0 && inD[i] == n-1){
                return i;
            }
        }
        return -1;
    }
};