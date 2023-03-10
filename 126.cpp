//
// Created by Siqing Zhang on 28/2/2023.
//

#include <string>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>

// asmt 6771
struct fileOpenException : public std::exception
{
    const char * errorMess;
    explicit fileOpenException(const char * message):errorMess(message){}
    [[nodiscard]] const char * what () const noexcept override
    {

        return errorMess;
    }
};


auto read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
    std::ifstream infile;
    infile.open(path,std::ios::in);
    std::optional<fileOpenException> failOpen;

    if (!infile.is_open()) {
        failOpen = fileOpenException("Cannot open the given file");
    }
    else if (infile.bad()) {
        failOpen = fileOpenException("Reading error");
    }
    if (failOpen.has_value()) throw failOpen.value();
    std::unordered_set<std::string> lexicon;
    std::string curLine;
    while(getline(infile,curLine)){
        lexicon.insert(curLine);
    }
    if (!infile.eof()) {
        failOpen = fileOpenException("Cannot get the file bottom");
    }
    if (failOpen.has_value()) throw failOpen.value();
    return lexicon;
}

void trackPath(const std::string &from, const std::string &to,
                  std::unordered_map<std::string, std::vector<std::string>> &next,
                  std::vector<std::string> &&path, std::vector<std::vector<std::string>> &result) {
    if (from == to) result.emplace_back(path); // base case
    for (const auto &w: next[from]) {
        auto path_{path};
        path_.emplace_back(w);  // move semantic instead of push+copy+pop when backtracking
        trackPath(w, to, next, std::move(path_), result);   // recursive case
    }
}


std::vector<std::vector<std::string>>
word_ladder(std::string from, std::string to, const std::unordered_set<std::string> &lexicon) {
    if (!lexicon.count(to) || !lexicon.count(from)) [[unlikely]]
        return std::vector<std::vector<std::string>>{};  // assumption 2 mismatching
    if (to == from) return std::vector<std::vector<std::string>>{{from}};

    // initialization
    std::unordered_set<std::string> visited{};
    visited.insert(from), visited.insert(to);

    std::unordered_set<std::string> forth{from}, back{to};
    std::unordered_map<std::string, std::vector<std::string>> next; // record the trace

    bool reversed, matching = false;

    while (!forth.empty()) {
        std::unordered_set<std::string> temp;   // forward set for next step
        for (const auto &w: forth) {   // for each word 'w' in current forward set
            for (std::size_t i = 0; i < w.size(); ++i) {   // for each letter in the current word
                auto cur_word = w;
                for (auto j = 'a'; j <= 'z'; ++j) {
                    cur_word[i] = j;
                    if (back.count(cur_word)) [[unlikely]] {    // bidirectional BFS rendezvous at cur_word
                        reversed ? next[cur_word].emplace_back(w) : next[w].emplace_back(cur_word);
                        matching = true;
                    }
                    if (!lexicon.count(cur_word) || visited.count(cur_word)) continue;   // track the path
                    reversed ? next[cur_word].emplace_back(w) : next[w].emplace_back(cur_word);
                    temp.insert(cur_word);
                }
            }
        }

        if (matching) [[unlikely]] break;   // break search
        for (const auto &w: temp) visited.insert(w);   // newly visited words this step
        if (temp.size() <= back.size()) forth = temp;   // choose the small one to explore next step
        else {
            reversed = !reversed;
            forth = back;
            back = temp;
        }
    }

    if (matching) {
        std::vector<std::vector<std::string>> result;
        trackPath(from, to, next, {from}, result); // get result
        return result;
    }
    return std::vector<std::vector<std::string>>{};
}



using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        auto &to = endWord;
        auto &from = beginWord;
        unordered_set<string> lexicon(wordList.begin(), wordList.end());


        if (!lexicon.count(to) || !lexicon.count(from))[[unlikely]]
            return std::vector<std::vector<std::string>>{};  // assumption 2 mismatching
        if (to == from) [[unlikely]] return std::vector<std::vector<std::string>>{{from}};

        // initialization
        std::unordered_set<std::string> visited{};
        visited.insert(from), visited.insert(to);

        std::unordered_set<std::string> forth{from}, back{to};
        std::unordered_map<std::string, std::vector<std::string>> next; // record the trace

        bool reversed, matching = false;

        while (!forth.empty()) {
            std::unordered_set<std::string> temp; // forward set for next step
            for (const auto &w: forth) { // for each word 'w' in current forward set
                for (auto i = 0; i < w.size(); ++i) { // for each letter in the current word
                    auto cur_word = w;
                    for (auto j = 'a'; j <= 'z'; ++j) {
                        cur_word[i] = j;
                        if (back.count(cur_word)) [[unlikely]] { // bidirectional BFS rendezvous at cur_word
                            reversed ? next[cur_word].emplace_back(w) : next[w].emplace_back(cur_word);
                            matching = true;
                        }
                        if (!lexicon.count(cur_word) || visited.count(cur_word)) continue;   // track the path
                        reversed ? next[cur_word].emplace_back(w) : next[w].emplace_back(cur_word);
                        temp.insert(cur_word);
                    }
                }
            }

            if (matching) [[unlikely]] break; // break search
            for (const auto &w: temp) visited.insert(w); // newly visited words this step
            if (temp.size() <= back.size()) forth = temp; // choose the small one to explore next step
            else {
                reversed = !reversed;
                forth = back;
                back = temp;
            }
        }

        if (matching) {
            std::vector<std::vector<std::string>> result;
            backtracking(from, to, next, {from}, result); // get result
            return result;
        }
        return std::vector<std::vector<std::string>>{};
    }

    void backtracking(const std::string &src, const std::string &dst,
                      std::unordered_map<std::string, std::vector<std::string>> &next,
                      std::vector<std::string> && path, std::vector<std::vector<std::string>> &result) {
        if (src == dst) result.emplace_back(path); // base case
        for (const auto &w: next[src]) {
//            path.emplace_back(w);
//            backtracking(w, dst, next, path, result);   // recursive case
//            path.pop_back();
            auto path_ {path};
            path_.emplace_back(w);
            backtracking(w, dst, next, std::move(path_), result);   // recursive case
        }
    }
};

class Solution2222 {
public:
    vector<vector<string>> ans;
    void dfs(unordered_map<string, unordered_set<string>> &str2parent, string &str, vector<string> &path, string &from) {
        if(str == from) {
            ans.emplace_back(path);
            return;
        }
        // 向前找
        for(auto s : str2parent[str]) {
            path.emplace_back(s);
            dfs(str2parent, s, path, from);
            path.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // 要求快速找到 a->b 只有一个元素之差
        // 双向BFS
        unordered_set<string> m(wordList.begin(), wordList.end());
        if(m.count(endWord) == 0) return ans;
        // BFS 建立图
        queue<string> que;
        que.emplace(beginWord);


        unordered_set<string> is_visited;

        unordered_map<string, unordered_set<string>> str2parent;


        is_visited.insert(beginWord);

        int len = 1;
        // 需要序列，所以需要保存图的信息
        bool flag = false;
        while(!que.empty()) {
            int size = que.size();
            unordered_set<string> level;
            for(int k = 0; k < size; ++k) {
                string str = que.front();
                que.pop();
                // 枚举下一个可能的单词
                for(int i = 0; i < str.length(); ++i) {
                    string next = str;
                    for(int j = 0; j < 26; ++j) {
                        next[i] = 'a' + j;
                        if(next[i] != str[i]) {
                            if(m.count(next) && !is_visited.count(next)) {
                                str2parent[next].insert(str);
                                // level 是用来存储下一层被访问到的节点，如果下一层的节点已经加入level，就不用再加入que
                                auto it = level.insert(next);
                                if(it.second) {
                                    que.emplace(next);
                                }
                            }
                        }
                        if(next == endWord) flag = true;
                    }
                }
            }
            // 把level的内容加入is_visited，这样保证不会访问到上几层已经访问过的元素
            // 其实就是同一层出现的元素是可以的，只是需要过滤掉上几层的已经
            //          red
            //      rex      ted
            //       |    /   |
            //      tex      tad
            //          tax
            for(auto &it : level) {
                is_visited.insert(it);
            }
            if(flag) break;

        }
        // debug

        // for(auto it : str2parent) {
        //     cout << it.first << ": ";
        //     for(auto from : it.second) {
        //         cout << from << " ";
        //     }
        //     cout << endl;
        // }

        // debug


        // 需要从 endword 重建转换序列
        // endword -> 的父辈
        vector<string> path = {endWord};
        dfs(str2parent, endWord, path, beginWord);
        for(int i = 0; i < ans.size(); ++i) {
            reverse(ans[i].begin(), ans[i].end());
        }
        return ans;

    }
};

// 作者：limbo-w
// 链接：https://leetcode.cn/problems/word-ladder-ii/solution/cbfs-dfs-guo-zui-xin-yang-li-by-limbo-w-cjet/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。