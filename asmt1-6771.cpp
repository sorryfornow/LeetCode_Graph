

#include <unordered_set>
#include <fstream>
#include <istream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <queue>

namespace word_ladder{
    auto read_lexicon(const std::string &path) -> std::unordered_set<std::string>;
    auto generate(
            const std::string &from,
            const std::string &to,
            const std::unordered_set<std::string> &lexicon
    ) -> std::vector<std::vector<std::string>>;
}


/**The function void trackPath(...) below is used to backtrack the path previously probed by Bi-BFS.
 * A std::vector 'result' saved any of possible path that valid with the shortest distance. Specifically,
 * adjacency_map[from] may return empty thus '.at' is inapplicable here. Furthermore, using C++ move
 * semantic to optimize the trans instead of maintain stack(std::vector) push+copy+pop while tracking.**/
void trackPath(const std::string &from, const std::string &to,
               std::unordered_map<std::string, std::vector<std::string>> &adjacency_map,
               std::vector<std::string> &&path, std::vector<std::vector<std::string>> &result) {
    if (from == to) result.emplace_back(std::move(path)); // base case
    for (const auto &word: adjacency_map[from]) {
        auto path_{path};
        path_.emplace_back(word);
        trackPath(word, to, adjacency_map, std::move(path_), result);   // recursive case
    }
}

auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
    std::ifstream infile(path.c_str(), std::ifstream::in);

    // check if assumption 4 valid
    std::optional<std::runtime_error> failOpen;
    if (!infile.is_open()) [[unlikely]] failOpen = std::runtime_error("Cannot open the given file");
    else if (infile.bad()) [[unlikely]] failOpen = std::runtime_error("Reading error");
    if (failOpen.has_value()) [[unlikely]] throw std::move(failOpen).value();

    // successfully open the given file now
    std::unordered_set<std::string> lexicon;
    std::string curLine;
    while (getline(infile, curLine)) lexicon.insert(curLine); // read lines(words) of dictionary

    if (!infile.eof()) [[unlikely]] failOpen = std::runtime_error("Cannot get the file bottom");
    if (failOpen.has_value()) [[unlikely]] throw std::move(failOpen).value();
    return lexicon;
}

auto word_ladder::generate(
        const std::string &from,
        const std::string &to,
        const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
    if (from.size() != to.size()) [[unlikely]]
        return std::vector<std::vector<std::string>>{}; // assumption 1 mismatching
    if (!lexicon.count(to) || !lexicon.count(from)) [[unlikely]]
        return std::vector<std::vector<std::string>>{};  // assumption 2 mismatching
    if (to == from) [[unlikely]]
        return std::vector<std::vector<std::string>>{{from}};  // assumption 3 mismatching

    // initialization
    std::unordered_set<std::string> visited{};  // record the visited words
    visited.insert(from), visited.insert(to);

    std::unordered_set<std::string> forth{from}, back{to};  // instead of queue, using std::set for rendezvous check
    std::unordered_map<std::string, std::vector<std::string>> adjacency_map; // record the next word

    bool hasChangedDirection = false;  // swap the direction
    bool getMatching = false;  // bidirectional BFS rendezvous check

    while (!forth.empty()) {
        std::unordered_set<std::string> temp{};   // provision of current orientation set for next probe
        for (const auto &last_word: forth) {   // for each word 'last_word' in forward set
            for (std::size_t i = 0; i < last_word.size(); ++i) {   // for each letter in the 'last_word'
                auto cur_word = last_word;
                for (auto j = 'a'; j <= 'z'; ++j) {
                    cur_word[i] = j;    // change the specific letter
                    if (back.count(cur_word)) [[unlikely]] {
                        // bidirectional BFS rendezvous at cur_word
                        getMatching = true;
                        // ternary is used to keep the direction of adjacency is always from-to
                        hasChangedDirection ? adjacency_map[cur_word].emplace_back(last_word)
                                            : adjacency_map[last_word].emplace_back(cur_word);
                    }
                    if (lexicon.count(cur_word) && !visited.count(cur_word)) {
                        // continuously track the possible path
                        temp.insert(cur_word);
                        hasChangedDirection ? adjacency_map[cur_word].emplace_back(last_word)
                                            : adjacency_map[last_word].emplace_back(cur_word);
                    }
                }
            }
        }

        if (getMatching) [[unlikely]] break;   // break search
        for (const auto &word: temp) visited.insert(word);   // newly visited words this step
        if (temp.size() <= back.size()) forth = temp;   // choose the small one to explore next step
        else {
            hasChangedDirection = not hasChangedDirection;  // swap the direction to search
            forth = std::move(back);
            back = std::move(temp);
        }
    }

    // no path exist from src to dst
    if (not getMatching) [[unlikely]] return std::vector<std::vector<std::string>>{};
    std::vector<std::vector<std::string>> result{};
    trackPath(from, to, adjacency_map, {from}, result);
    std::sort(result.begin(), result.end()); // sort the result
    return result;  // get result
}