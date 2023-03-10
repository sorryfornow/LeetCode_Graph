//
// Created by Siqing Zhang on 2022/8/21.
//
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<char, vector<char>> edges;
    unordered_map<char, int> indegrees;
    bool valid = true;

    void addEdge(string word1, string word2){
        int l1 = word1.size();
        int l2 = word2.size();
        int l0 = min(l1,l2);
//        bool l1isBig = false;
//        l1 > l2 ? l0 = l2, l1isBig = true : l0 = l1;

        int i = 0;
        while(i < l0){
            char c1 = word1[i];
            char c2 = word2[i];
            if (c1!=c2){
                edges[c1].emplace_back(c2);
                indegrees[c2]+=1;
                break;
            }
            i++;
        }
        // w2 is the prefix of w1
        if (l1>l2 && i == l0){
            valid = false;
        }
    }

    string alienOrder(vector<string>& words) {
        // convert all characters in words to vertices
        int length = words.size();
        for (auto & word: words){
            int wLength = word.size();
            for (auto &letter: word){
                if(edges.count(letter)==0){
                    edges[letter] = vector<char>();
                    // indegrees[letter] = 0;
                }
            }
        }

        for (int i = 1; i < length ; i++) {
            addEdge(words[i - 1], words[i]);
            if (!valid) {
                return "";
            }
        }

        queue<char> Q;
        // add the word into queue with in-degree 0
        for (auto & edge : edges) {
            if (indegrees.count(edge.first) == 0) {
                Q.emplace(edge.first);
            }
        }

        //topological ordering
        string order;
        while (!Q.empty()) {
            char u = Q.front();
            Q.pop();
            order.push_back(u);

            for (char & v : edges[u]) {
                indegrees[v]--;
                if (indegrees[v] == 0) {
                    Q.emplace(v);
                }
            }
        }

        return order.size() == edges.size() ? order : "";

    }
};