
// http://codeforces.com/contest/559/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t; cin >> s >> t;
    function<string(string)> swap_sort = [&] (string s) {
        auto res = s;
        if(s.size() % 2 == 0) {
            auto sl = swap_sort(s.substr(0, s.size() / 2));
            auto sr = swap_sort(s.substr(s.size() / 2, s.size() / 2));
            if(sl < sr) res = sl + sr;
            else        res = sr + sl;
        }
        return res;
    };
    cout << (swap_sort(move(s)) == swap_sort(move(t)) ? "YES" : "NO") << endl;
}
