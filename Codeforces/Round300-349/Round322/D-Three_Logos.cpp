// http://codeforces.com/contest/581/problem/D

#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> h(3), w(3);
    int S = 0;
    for(int i = 0; i < 3; ++i) {
        cin >> h[i] >> w[i];
        S += h[i] * w[i];
    }
    int len = 0;
    while(len * len < S) len++;
    if(len * len != S) {
        cout << -1 << endl;
        return 0;
    }
    vector<string> ans(len, string(len, '.'));
    for(int d1 = 0; d1 < 2; ++d1) {
        for(int d2 = 0; d2 < 2; ++d2) {
            for(int d3 = 0; d3 < 2; ++d3) {
                if(w[0] == len && w[1] == len && w[2] == len) {
                    int yp = 0;
                    for(int i = 0; i < 3; ++i) {
                        for(int y = yp; y < yp + h[i]; ++y) {
                            for(int x = 0; x < len; ++x) {
                                ans[y][x] = 'A' + i;
                            }
                        }
                        yp += h[i];
                    }
                }
                for(int i = 0; i < 3; ++i) {
                    const int j = (i + 1) % 3, k = (i + 2) % 3;
                    if(w[i] == len && h[j] == h[k] && h[i] + h[j] == len && w[j] + w[k] == len) {
                        for(int y = 0; y < h[i]; ++y) {
                            for(int x = 0; x < len; ++x) {
                                ans[y][x] = 'A' + i;
                            }
                        }
                        for(int y = h[i]; y < len; ++y) {
                            for(int x = 0; x < len; ++x) {
                                ans[y][x] = 'A' + (x < w[j] ? j : k);
                            }
                        }
                    }
                }
                swap(h[2], w[2]);
            }
            swap(h[1], w[1]);
        }
        swap(h[0], w[0]);
    }

    if(ans[0][0] == '.') {
        cout << -1 << endl;
    } else {
        cout << len << endl;
        for(auto& s : ans) {
            cout << s << endl;
        }
    }
}
