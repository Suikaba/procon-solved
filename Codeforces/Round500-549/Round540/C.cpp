#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    map<int, int> cnt;
    for(int i = 0; i < n * n; ++i) {
        int a; cin >> a;
        cnt[a] += 1;
    }

    vector<vector<int>> ans(n, vector<int>(n));
    { // check
        int one = -1;
        vector<int> two;
        for(const auto& p : cnt) {
            if(p.second % 4 != 0 && n % 2 == 0) {
                cout << "NO" << endl;
                return 0;
            }
            if(p.second % 4 == 1 || p.second % 4 == 3) {
                if(one != -1) {
                    cout << "NO" << endl;
                    return 0;
                }
                one = p.first;
                if(p.second % 4 == 3) {
                    two.push_back(p.first);
                }

            } else if(p.second % 4 == 2) {
                two.push_back(p.first);
            }
        }

        if((int)two.size() > n / 2 * 2) {
            cout << "NO" << endl;
            return 0;
        }

        if(one != -1) {
            ans[n / 2][n / 2] = one;
            cnt[one] -= 1;
            assert(cnt[one] % 4 == 0 || cnt[one] % 4 == 2);
        }
        for(int i = 0; i < (int)two.size(); ++i) {
            if(i < n / 2) {
                ans[n / 2][i] = ans[n / 2][n - i - 1] = two[i];
                cnt[two[i]] -= 2;
            } else {
                const int j = i - n / 2;
                ans[j][n / 2] = ans[n - j - 1][n / 2] = two[i];
                cnt[two[i]] -= 2;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(ans[i][j] != 0) continue;
            if((n & 1) && (i == n / 2 || j == n / 2)) {
                bool ok = false;
                for(auto& p : cnt) {
                    if(p.second % 4 == 2) {
                        ok = true;
                        ans[i][j] = ans[n - i - 1][n - j - 1] = p.first;
                        p.second -= 2;
                        break;
                    }
                }
                if(ok) continue;
            }
            for(auto& p : cnt) {
                if(p.second == 0) continue;
                if((n & 1) && (i == n / 2 || j == n / 2)) {
                    ans[i][j] = ans[n - i - 1][n - j - 1] = p.first;
                    p.second -= 2;
                    break;
                } else if(p.second != 2) {
                    ans[i][j] = ans[n - 1 - i][j] = ans[i][n - j - 1] = ans[n - i - 1][n - j - 1] = p.first;
                    p.second -= 4;
                    break;
                }
            }
        }
    }

    cout << "YES" << endl;
    //for(auto& p : cnt) {
    //    assert(p.second == 0);
    //}
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << ans[i][j] << " \n"[j + 1 == n];
        }
    }
    cout << flush;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            assert(ans[i][j] != 0);
            assert(ans[i][j] == ans[n - i - 1][j]);
            assert(ans[i][j] == ans[i][n - j - 1]);
        }
    }
}
