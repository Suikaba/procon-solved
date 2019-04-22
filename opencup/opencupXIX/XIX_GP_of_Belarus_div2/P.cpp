#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    string cell;
    {
        string s;
        while(cin >> s) {
            cell += s;
        }
    }
    auto get = [&] (vector<int> const& pos) {
        int idx = 0;
        for(auto x : pos) {
            idx *= 3;
            idx += x;
        }
        return cell[idx];
    };


    int x = 0, o = 0;
    vector<int> tmp;
    function<void(vector<int>&)> solve = [&] (vector<int>& v) {
        if((int)v.size() == n) {
            if(count(begin(v), end(v), 0) == n) return;
            vector<int> p(n, -100);
            for(int i = 0; i < n; ++i) {
                if(v[i] == 1) p[i] = 0;
                else if(v[i] == -1) p[i] = 2;
            }
            function<void(int, vector<int>&)> dfs = [&] (int d, vector<int>& pos) {
                if(d == n) {
                    const auto c = get(pos);
                    if(c == '.') return;
                    auto cur = pos;
                    for(int lp = 0; lp < 2; ++lp) {
                        for(int i = 0; i < n; ++i) {
                            cur[i] += v[i];
                        }
                        if(get(cur) != c) return;
                    }
                    if(c == 'X') x += 1;
                    else         o += 1;
                    return;
                }
                if(pos[d] == -100) {
                    for(int i = 0; i <= 2; ++i) {
                        pos[d] = i;
                        dfs(d + 1, pos);
                    }
                    pos[d] = -100;
                } else {
                    dfs(d + 1, pos);
                }
            };
            dfs(0, p);
            return;
        }
        for(int i = -1; i <= 1; ++i) {
            v.push_back(i);
            solve(v);
            v.pop_back();
        }
    };
    solve(tmp);
    x /= 2, o /= 2;

    cout << "X scores " << x << " and O scores " << o << endl;
}
