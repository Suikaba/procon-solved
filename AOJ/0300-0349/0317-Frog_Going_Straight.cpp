#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0317

int main() {
    int d, l;
    cin >> d >> l;
    cout << (d % l) + (d / l) << endl;
}
