//
// Created by Siqing Zhang on 14/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

// UnionFindSet 模版
class UnionFind{
public:
    int find(int x){
        int root = x;

        while(father[root] != -1){
            root = father[root];
        }

        while(x != root){
            int original_father = father[x];
            father[x] = root;
            x = original_father;
        }

        return root;
    }

    bool is_connected(int x,int y){
        return find(x) == find(y);
    }

    void merge(int x,int y){
        int root_x = find(x);
        int root_y = find(y);

        if(root_x != root_y){
            father[root_x] = root_y;
        }
    }

    void add(int x){
        if(!father.count(x)){
            father[x] = -1;
        }
    }

private:
    // 记录父节点
    unordered_map<int,int> father;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {

    }
};