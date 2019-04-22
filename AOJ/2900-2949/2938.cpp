#include <bits/stdc++.h>
using namespace std;

char M(char a, char b) {
    if(a == 'T' && b == 'F') return 'F';
    return 'T';
}

int main() {
    int n; cin >> n;
    char ans; cin >> ans;
    for(int i = 1; i < n; ++i) {
        char b; cin >> b;
        ans = M(ans, b);
    }
    cout << ans << endl;
}