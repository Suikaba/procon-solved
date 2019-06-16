#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while(cin >> n, n) {
        vector<string> ws(n);
        for(auto& w : ws) cin >> w;
        vector<string> ss = {""};
        while(cin >> ss.back()) {
            if(ss.back().back() == '.') break;
            ss.push_back("");
        }
        ss.back().pop_back(); // period
        const auto ts = ss;
        sort(begin(ss), end(ss), [] (string s1, string s2) {
                return set<char>{begin(s1), end(s1)}.size() > set<char>{begin(s2), end(s2)}.size();
            });

        auto conv = [] (string s, vector<char> const& m) {
            for(auto& c : s) {
                c = m[c - 'A'];
            }
            return s;
        };
        string ans;
        function<void(int, vector<char>)> dfs = [&] (int i, vector<char> m) {
            if(ans == "-.") return;
            if(i == (int)ss.size()) {
                string tans = conv(ts[0], m);
                for(int j = 1; j < (int)ts.size(); ++j) {
                    tans += " " + conv(ts[j], m);
                }
                tans += ".";
                if(!ans.empty() && ans != tans) {
                    ans = "-.";
                } else {
                    ans = tans;
                }
                return;
            }
            const auto& s = ss[i];
            for(auto const& w : ws) {
                if(s.size() != w.size()) continue;
                bool check = true;
                vector<char> tm = m;
                for(int j = 0; j < (int)s.size(); ++j) {
                    check &= m[s[j] - 'A'] == w[j] || (m[s[j] - 'A'] == '*' && m[w[j] - 'A'] == '*');
                    tm[s[j] - 'A'] = w[j];
                    tm[w[j] - 'A'] = s[j];
                }
                if(!check) continue;
                dfs(i + 1, move(tm));
            }
        };
        dfs(0, vector<char>(26, '*'));

        cout << ans << endl;
    }
}
