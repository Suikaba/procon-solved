// BEGIN CUT HERE
// END CUT HERE

#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

//template<typename T>
//std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }
//
//template <class... Args>
//auto table(int n, Args... args) {
//    auto val = table(args...);
//    return std::vector<decltype(val)>(n, std::move(val));
//}

class ThreeSameLetters {
public:
    int countStrings(int L, int S) {
        if(L <= 2) {
            return 0;
        }
        vector<vector<vector<vector<int>>>> dp(L + 1, vector<vector<vector<int>>>(S + 1, vector<vector<int>>(S + 1, vector<int>(2))));
        for(int i = 0; i < S; ++i) {
            for(int j = 0; j < S; ++j) {
                dp[2][i][j][0] = 1;
            }
        }
        for(int i = 2; i < L; ++i) {
            for(int c1 = 0; c1 < S; ++c1) {
                for(int c2 = 0; c2 < S; ++c2) {
                    for(int c3 = 0; c3 < S; ++c3) {
                        if(c1 == c2 && c2 == c3) {
                            (dp[i + 1][c2][c3][1] += dp[i][c1][c2][0]) %= mod;
                        } else {
                            (dp[i + 1][c2][c3][1] += dp[i][c1][c2][1]) %= mod;
                            (dp[i + 1][c2][c3][0] += dp[i][c1][c2][0]) %= mod;
                        }
                    }
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < S; ++i) {
            for(int j = 0; j < S; ++j) {
                (ans += dp[L][i][j][1]) %= mod;
            }
        }

        return ans;
    }
};
