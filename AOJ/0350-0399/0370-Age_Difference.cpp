// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0370

#include <bits/stdc++.h>
using namespace std;

int main() {
    array<tuple<int, int, int>, 2> birth;
    for(int i = 0; i < 2; ++i) {
        cin >> get<0>(birth[i]) >> get<1>(birth[i]) >> get<2>(birth[i]);
    }
    if(birth[0] > birth[1]) swap(birth[0], birth[1]);
    int ans = get<0>(birth[1]) - get<0>(birth[0]);
    if(make_pair(get<1>(birth[0]), get<2>(birth[0])) < make_pair(get<1>(birth[1]), get<2>(birth[1]))) {
        ans += 1;
    }
    cout << ans << endl;
}
