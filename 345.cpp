//
// Created by Siqing Zhang on 19/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
private:
    const set<char> vowel = {'a','e','i','o','u','A','E','I','O','U'} ;
public:
    string reverseVowels(string s) {
        stack<char> stk;
        vector<int> pos;
        int n = s.size();
        for (int i=0;i<n;++i){
            if (vowel.count(s[i])){
                stk.push(s[i]);
                pos.emplace_back(i);
            }
        }

        for (const int & p:pos) {
            char tmp = stk.top();
            stk.pop();
            s[p] = tmp;
        }
        return s;
    }
};