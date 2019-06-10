#include <bits/stdc++.h>
using namespace std;

vector<string> split(string const& s) {
    string cur;
    vector<string> res;
    for(auto c : s) {
        if(c == ' ') {
            if(cur.size() != 0) {
                res.push_back(cur);
            }
            cur = "";
        } else {
            cur += c;
        }
    }
    if(cur.size() != 0) res.push_back(cur);
    return res;
}

int main() {
    vector<vector<string>> ls;
    int len = 0;
    { // input
        ifstream ifs("alignment.in");
        if(!ifs) assert(false);
        string line;
        while(getline(ifs, line)) ls.push_back(split(line));
        for(auto const& ss : ls) len = max(len, (int)ss.size());
    }
    const int n = ls.size();

    vector<int> pos(n);
    vector<string> ans(n);
    for(int i = 0; i < len; ++i) {
        int nxt_p = 0;
        if(i != 0) {
            for(int j = 0; j < n; ++j) {
                nxt_p = max(nxt_p, (int)ans[j].size() + 1);
            }
        }
        for(int j = 0; j < n; ++j) {
            if((int)ls[j].size() <= i) continue;
            while((int)ans[j].size() < nxt_p) ans[j] += ' ';
            ans[j] += ls[j][i];
        }
    }

    ofstream ofs("alignment.out");
    for(auto const& s : ans) {
        ofs << s << endl;
    }
}
