#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> vs;
    string s;
    while(cin >> s) {
        if(s.back() == '?' && !vs.empty() && vs[0] == "What") {
            vs[0] = "Forty-two";
            s.back() = '.';
            vs.emplace_back(s);
            const int sz = vs.size();
            for(int i = 0; i < sz; ++i) {
                cout << vs[i] << " \n"[i + 1 == sz];
            }
            vs.clear();
        } else if(s.back() == '?' || s.back() == '.') {
            vs.clear();
        } else {
            vs.push_back(s);
        }
    }
}