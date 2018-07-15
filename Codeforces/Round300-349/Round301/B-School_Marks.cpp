
// http://codeforces.com/contest/540/problem/B

// lt + ge < n 抜け忘れまくりで最悪．
// 1 を置きまくるんだから，y == 1 のときに気にしなくちゃいけないのは当然なんですが…
// 極端な例ぐらいちゃんと考えようね．

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, p, x, y;
    cin >> n >> k >> p >> x >> y;
    vector<int> a(k);
    int lt = 0, ge = 0, sum = 0;
    for(int i = 0; i < k; ++i) {
        cin >> a[i];
        lt += a[i] < y;
        ge += a[i] >= y;
        sum += a[i];
    }

    vector<int> ans;
    while(lt < (n - 1) / 2 && lt + ge < n) {
        ans.push_back(1);
        sum += 1;
        lt++;
    }
    while(ge + lt < n) {
        ans.push_back(y);
        sum += y;
        ge++;
    }

    if(lt > (n - 1) / 2 || sum > x) {
        cout << -1 << endl;
    } else {
        const int m = ans.size();
        for(int i = 0; i < m; ++i) {
            cout << ans[i] << " \n"[i + 1 == m];
        }
    }
}
