//
// Created by Siqing Zhang on 2022/8/19.
// 联通无环图
//
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (n < 2){
            return true;
        }
        if (edges.size() != n-1) {
            return false;
        }
        // BFS
        vector<int> visited(n,0); // visited list
//        for (int & v:visited){
//            v = 0;
//        }
//        unordered_map<int,vector<int>> adjList;
//        for (vector<int>& adj:edges) {
//
//        }
        queue<int> Q;
        Q.push(0);
        int vCount = 0; // visited number

        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            vCount++;
            visited[u] = 1;
            for (vector<int> &adj: edges) {
                if (adj[0] == u) {
                    if (visited[adj[1]]){
                        return false;
                    }
                    Q.push(adj[1]);
                }
            }
        }
        return n == vCount;

    }
};