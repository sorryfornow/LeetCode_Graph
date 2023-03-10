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
    bool dfs(int curNode,int curGroup,vector<int>& group, unordered_map<int,vector<int>>& bipar){
        group[curNode] = curGroup;
        int nextGroup = -curGroup;
        for (auto& nextnode : bipar[curNode]) {
            if (group[nextnode]){
                if (group[nextnode]==group[curNode]){
                    return false;
                }
            } else{
                if (!dfs(nextnode,nextGroup,group,bipar)){
                    return false;
                }
            }
        }
        return true;
    }
    bool possibleBipartition(int n, vector<vector<int>> &dislikes) {
        unordered_map<int,vector<int>> bipar;
        vector<int> group(n+1,0); // 1 -1
        for (auto & pa: dislikes) {
            bipar[pa[0]].emplace_back(pa[1]);
            bipar[pa[1]].emplace_back(pa[0]);
        }
        for (int i = 1; i <= n; ++i) {
            if (group[i] == 0 && !dfs(i, 1, group, bipar)) {
                return false;
            }
        }
        return true;
    }
};