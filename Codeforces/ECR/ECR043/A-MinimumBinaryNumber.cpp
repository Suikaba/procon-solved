#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    if(s == "0") {
        cout << s << endl;
    } else {
        int cnt = count(begin(s), end(s), '0');
        string ans = "1" + string(cnt, '0');
        cout << ans << endl;
    }
}
