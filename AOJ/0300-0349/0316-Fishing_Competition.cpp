#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0316

int main() {
    vector<int> iwana(2), yamame(2);
    for(int i = 0; i < 2; ++i) {
        cin >> iwana[i] >> yamame[i];
    }
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    vector<int> s(2);
    for(int i = 0; i < 2; ++i) {
        s[i] = iwana[i] * a + yamame[i] * b + iwana[i] / 10 * c + yamame[i] / 20 * d;
    }

    if(s[0] > s[1]) cout << "hiroshi" << endl;
    else if(s[0] < s[1]) cout << "kenjiro" << endl;
    else cout << "even" << endl;
}
