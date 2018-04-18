#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1252

constexpr int inf = 1e9;

int levenshtein_distance(string s1, string s2) {
    const int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, inf));
    for(int i = 0; i <= n; ++i) dp[i][0] = i;
    for(int j = 0; j <= m; ++j) dp[0][j] = j;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            dp[i][j] = min({dp[i][j],
                            dp[i - 1][j] + 1,
                            dp[i][j - 1] + 1,
                            dp[i - 1][j - 1] + (s1[i - 1] != s2[j - 1])});
        }
    }
    return dp[n][m];
}

int main() {
    int n;
    while(cin >> n, n) {
        int d;
        cin >> d;
        vector<string> name(n);
        for(int i = 0; i < n; ++i) {
            cin >> name[i];
        }

        vector<string> ans;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                auto s1 = name[i], s2 = name[j];
                if(s1.size() < s2.size()) swap(s1, s2);
                const int m = s1.size();

                int min_d = levenshtein_distance(s1, s2);

                // swap -> levenshtein
                for(int k = 0; k + 1 < m; ++k) {
                    swap(s1[k], s1[k + 1]);
                    min_d = min(min_d, levenshtein_distance(s1, s2) + 1);
                    swap(s1[k], s1[k + 1]);
                }

                // swap -> swap
                for(int k = 0; k + 1 < m && min_d >= 3; ++k) {
                    swap(s1[k], s1[k + 1]);
                    for(int l = 0; l + 1 < m; ++l) {
                        swap(s1[l], s1[l + 1]);
                        if(s1 == s2) min_d = 2;
                        swap(s1[l], s1[l + 1]);
                    }
                    swap(s1[k], s1[k + 1]);
                }

                // delete -> swap
                for(int k = 0; k < m && min_d >= 3; ++k) {
                    auto ss1 = (k == 0 ? string("") : s1.substr(0, k)) + (k + 1 == m ? string("") : s1.substr(k + 1));
                    for(int l = 0; l + 1 < m - 1; ++l) {
                        swap(ss1[l], ss1[l + 1]);
                        if(ss1 == s2) min_d = 2;
                        swap(ss1[l], ss1[l + 1]);
                    }
                }

                if(min_d <= d) {
                    ans.push_back(min(name[i], name[j]) + "," + max(name[i], name[j]));
                }
            }
        }

        sort(begin(ans), end(ans));
        for(auto x : ans) {
            cout << x << endl;
        }
        cout << ans.size() << endl;
    }
}