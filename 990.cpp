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
    vector<int> rank;
    UnionFindSet(const vector<int> roots){
        this->roots = roots;
        this->rank = vector<int>(roots.size(),1);
    }
    UnionFindSet(const int n){
        this->roots = vector<int> (n);
        for (int i = 0; i < n; ++i) {
            this->roots[i] = i;
        }
        this->rank = vector<int>(n,1);
    }

    int findRoot(int x){
        if (roots[x]==x){
            return x;
        }
        return roots[x] = findRoot(roots[x]);
    }

    void Union(int u, int v){
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);
        if (uRoot!=vRoot){
            if (rank[uRoot] > rank[vRoot]){
                roots[vRoot] = uRoot;
            } else if (rank[uRoot] < rank[vRoot]){
                roots[uRoot] = vRoot;
            } else{
                roots[vRoot] = uRoot; //相等把v的Root接在 u的Root 上
                rank[uRoot]++;
            }
        }
    }

    bool sameRoot(int u, int v){
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);
        if (uRoot==vRoot){
            return true;
        } else{
            return false;
        }
    }
};


class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        int nOfVars = 0;

        vector<pair<int,int>> equs;
        vector<pair<int,int>> inequs;
        unordered_map<char,int> vars;

        for(auto& eq:equations){
            if (vars.find(eq[0])==vars.end()){
                vars[eq[0]]= nOfVars++;
            }
            if (vars.find(eq[3])==vars.end()){
                vars[eq[3]]= nOfVars++;
            }
            if (eq[1] == '='){
                equs.emplace_back(make_pair(vars[eq[0]],vars[eq[3]]));
            } else{
                inequs.emplace_back(make_pair(vars[eq[0]],vars[eq[3]]));
            }
        }

        if(inequs.size()==0){
            return true;
        }

        auto UFS = UnionFindSet(nOfVars);
        for (auto &edge:equs){
            UFS.Union(edge.first,edge.second);
        }
        for (auto &edge:inequs){
            if(UFS.sameRoot(edge.first,edge.second)){
                return false;
            }
        }
        return true;
    }
};