#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1173&lang=jp

// 反省点
// 誤読があった．対応するカッコの組の間でカッコがバランスしている，という条件を見落としていた．
// A, B は少しぐらい遅くてもいいから誤読しないようにしないとそのまま予選敗退になるので注意．

int main() {
    string s;
    while(getline(cin, s), s != ".") {
        string t;
        for(auto c : s) {
            if(c == '(' || c == ')' || c == '[' || c == ']') t += c;
        }
        stack<char> st;
        bool ok = true;
        for(auto c : t) {
            if(c == '(' || c == '[') st.push(c);
            else if(c == ')') {
                if(st.empty() || st.top() != '(') {
                    ok = false;
                    break;
                }
                st.pop();
            } else if(c == ']') {
                if(st.empty() || st.top() != '[') {
                    ok = false;
                    break;
                }
                st.pop();
            }
        }
        ok &= st.empty();
        cout << (ok ? "yes" : "no") << endl;
    }
}
