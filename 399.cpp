//
// Created by Siqing Zhang on 16/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class UnionFindSet{
public:
    vector<int> roots;
    vector<double> weight;
    vector<int> rank;
    UnionFindSet(int n){
        this->roots = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            this->roots[i] = i;
        }
        this->weight = vector<double>(n,1.0);
        this->rank = vector<int>(this->roots.size(),1);
    }

    int findRoot(int x){
        // 伴随find函数更新weight
        if(roots[x] == x){
            return x;
        } else{
            int tmpRoot = roots[x];
            roots[x] = findRoot(roots[x]);
            weight[x] *= weight[tmpRoot];
        }
        return roots[x];
    }

    void Union(int u,int v, double value){
        // 伴随更新weight,
        // w_i = w_f * w_c * w_i,
        // w_i为每一个链接在u上的w
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);
        if (uRoot != vRoot){
            roots[uRoot] = vRoot;
            weight[uRoot] = value * weight[v] / weight[u];
        }
    }

    double query(int u, int v){
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);
        if(uRoot == vRoot){
            return weight[u] / weight[v];
        }
        return -1.0;
    }

};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {

        int nOfVars=0;
        vector<double> result;

        // transfer input from string to int
        vector<pair<int, double>> edges;
        unordered_map<string,int> vars;
        for (const auto & equ: equations){
            if (vars.find(equ[0])==vars.end()){
                vars[equ[0]]= nOfVars++;
            }
            if (vars.find(equ[1])==vars.end()){
                vars[equ[1]]= nOfVars++;
            }
            edges.emplace_back(make_pair(vars[equ[0]],vars[equ[1]]));
        }

        auto UFS = UnionFindSet(nOfVars);
        for (int i = 0;i<edges.size();++i){
            UFS.Union(edges[i].first,edges[i].second,values[i]);
        }
        for (int i = 0; i < nOfVars; ++i) {
            UFS.findRoot(i);
        }
        for (const auto & query:queries){
            if (vars.count(query[0])==0 || vars.count(query[1])==0){
                result.emplace_back(-1.0);
                continue;
            }
            int u = vars[query[0]];
            int v = vars[query[1]];
            result.emplace_back(UFS.query(u,v));
        }
        return result;
    }
};