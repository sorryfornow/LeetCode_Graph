#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        int n = s.size();
        vector<string> ans;
        auto f = [&](int i, int j) {
            vector<string> res;
            for (int k = 1; k <= j - i; ++k) {
                string l = s.substr(i, k);
                string r = s.substr(i + k, j - i - k);
                // bool ok = (l == "0" || l[0] != '0') && r.back() != '0';
                // 不添加小数点和添小数点后的整数部分都需要满足当前表示数字为 0 或者为不含前导零的正数。
                // 添加小数点后，小数部分需要满足其末尾不为 0。
                if ((l == "0" || l[0] != '0') && r.back() != '0') {
                    res.push_back(l + (k < j - i ? "." : "") + r);
                }
            }
            return res;
        };
        for (int i = 2; i < n - 1; ++i) {   // fractional point
            for (auto& x : f(1, i)) {       // all posibility for [1,i]
                for (auto& y : f(i, n - 1)) {   // combine all posibility fro [i,n-1]
                    ans.emplace_back("(" + x + ", " + y + ")");
                }
            }
        }
        return ans;
    }
};