//
// Created by Siqing Zhang on 14/10/2022.
//

#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;


class Solution1 {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n==0){
            return vector<int>{0};
        }

        // vector<int> degree (n,0);
        unordered_map<int,vector<int>> degree;
        for (auto &edge :edges){
            degree[edge[0]].emplace_back(edge[0]);
            degree[edge[1]].emplace_back(edge[1]);
            // degree[edge[0]]++;
            // degree[edge[1]]++;
        }

        queue<int> Q;
        vector<int> result;

        for (int i=0;i<n;++i){
            if (degree[i].size() < 2){
                Q.push(i);
            }
        }

        queue<int> Q1;
        while (!Q.empty()){
            // stack<int>().swap(result); // clear
            result.clear();
            int Qs = Q.size();
            for(int j= 0; j<Qs ; ++j){
                int u = Q.front();
                Q.pop();
                // result.push(u);
                result.emplace_back(u);

                int v = degree[u].front();
                //degree[u].pop_back();
                degree[u].clear();

                //vector<int>::iterator iter = find(degree[v].begin(),degree[v].end(), u);
                //int index = distance(degree[v].begin(), iter);
                for(int i=0; i<degree[v].size(); ++i){
                    if (degree[v][i] == u){
                        degree[v].erase(degree[v].begin()+i);
                    }
                }

                if (degree[v].size() < 2){
                    Q.push(v);
                    // result.push(v);
                }
            }
        }
        return result;

    }
};

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }
        vector<int> degree(n);
        vector<vector<int>> adj(n);
        for (auto & edge : edges){
            adj[edge[0]].emplace_back(edge[1]);
            adj[edge[1]].emplace_back(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }
        queue<int> Q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                Q.emplace(i);
            }
        }

        int remain = n;
        while (remain>2){
            int Qs = Q.size();
            remain -= Qs;
            for (int i = 0; i < Qs; i++) {
                int curr = Q.front();
                Q.pop();
                for (auto &v: adj[curr]) {
                    if (--degree[v] == 1) {
                        Q.emplace(v);
                    }
                }
            }
        }

        vector<int> result;
        while (!Q.empty()) {
            result.emplace_back(Q.front());
            Q.pop();
        }
        return result;
    }
};