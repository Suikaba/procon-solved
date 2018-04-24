// BEGIN CUT HERE
// END CUT HERE

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int number(string const& s, int& p) {
    bool neg = s[p] == '-';
    if(neg) p++;
    int res = 0;
    while(p < (int)s.size() && isdigit(s[p])) {
        res *= 10;
        res += s[p++] - '0';
    }
    return neg ? -res : res;
}

pii parse(string const& s) {
    int p = 0;
    int x = number(s, p);
    p++;
    int y = number(s, p);
    return {x, y};
}

constexpr int dx[8] = {2, 2, 1, 1, -2, -2, -1, -1};
constexpr int dy[8] = {1, -1, 2, -2, 1, -1, 2, -2};

class GeneralChess {
public:
    vector <string> attackPositions(vector <string> pieces) {
        set<pii> ans;
        {
            auto p = parse(pieces[0]);
            for(int i = 0; i < 8; ++i) {
                ans.emplace(p.first + dx[i], p.second + dy[i]);
            }
        }
        for(int i = 1; i < (int)pieces.size(); ++i) {
            set<pii> nans;
            auto p = parse(pieces[i]);
            for(int j = 0; j < 8; ++j) {
                auto p2 = make_pair(p.first + dx[j], p.second + dy[j]);
                if(ans.count(p2)) {
                    nans.insert(p2);
                }
            }
            ans = move(nans);
        }

        vector<string> ret;
        for(auto& p : ans) {
            ret.push_back(to_string(p.first) + "," + to_string(p.second));
        }

        return ret;
    }
};
