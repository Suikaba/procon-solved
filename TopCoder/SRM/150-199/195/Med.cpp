#include <bits/stdc++.h>
using namespace std;

// SRM195 Div1 Med

constexpr int inf = 1e9;

class SimpleIO {
public:
    int worstCase(string pattern, int target) {
        const int n = pattern.size();
        const auto s = pattern + pattern;
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            int max_len = 0;
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                int cnt = inf;
                for(int k = 1; k <= n; ++k) {
                    if(s[i + k] != s[j + k]) {
                        cnt = k;
                        break;
                    }
                }
                if(cnt == inf) {
                    max_len = inf;
                    break;
                }
                const int cur_pos = (i + cnt) % n;
                const int add = (target - cur_pos + n) % n;
                max_len = max(max_len, cnt + add);
            }
            ans = max(ans, max_len);
        }

        if(ans == inf) return -1;
        else return ans;
    }
};

//int main() {
//    SimpleIO simple;
//    cout << simple.worstCase("BNB", 0) << endl;
//    cout << simple.worstCase("BNBNBNBN", 3) << endl;
//    cout << simple.worstCase("BBNNBNBBBBNBBBBBB", 3) << endl;
//}
