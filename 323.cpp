//
// Created by Siqing Zhang on 14/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class unionSearch{
public:
    vector<int> roots;
    vector<int> rank;
    int mergeCount = 0;
    unionSearch(vector<int> roots){
        this->roots = roots;
        this->rank = vector<int>(roots.size(),1);
    }

    int find(int x){ // 查找component中作代表的vertex
        if(roots[x] == x){
            return x;
        }
        return roots[x] = find(roots[x]);
    }

    void merge(int u, int v){
        int uRoot = find(u);
        int vRoot = find(v);
        if (uRoot != vRoot){
            mergeCount++;
            if(rank[uRoot] >= rank[vRoot]){
                roots[vRoot] = uRoot;
            } else{
                roots[uRoot] = vRoot;
            }
            if(rank[uRoot] == rank[vRoot]){
                rank[uRoot]++; // rank相等情况发生时 u作为root
            }
        }
    }

};

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> roots(n);
        for (int i = 0; i < n; ++i) {
            roots[i] = i;
        }
        auto US = unionSearch(roots);
        for(auto &edge:edges){
            US.merge(edge[0],edge[1]);
        }
        return n - US.mergeCount;
    }

};

