#include <bits/stdc++.h>
using namespace std;

// ‚±‚êŒ™‚¢

int main() {
    int n; cin >> n;
    vector<int> cnt(4);
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        if(a == 0) continue;
        cnt[a - 1] += 1;
    }

    int ans = 0;
    { // 2 + 1 -> 3
        const int t = min(cnt[0], cnt[1]);
        ans += t;
        cnt[2] += t;
        cnt[0] -= t;
        cnt[1] -= t;
    }
    { // merge 1s to 3
        const int thr = cnt[0] / 3;
        ans += thr * 2;
        cnt[2] += thr;
        cnt[0] %= 3;
    }
    { // merge 2s to 3
        const int thr = cnt[1] / 3 * 2;
        ans += thr;
        cnt[2] += thr;
        cnt[1] %= 3;
    }
    if(cnt[0] == 1 && cnt[2] > 0) {
        cnt[0] = 0; cnt[2] -= 1;
        cnt[3] += 1;
        ans += 1;
    }
    if(cnt[0] == 2 && cnt[3] > 0) {
        cnt[0] = 0; cnt[3] -= 1;
        cnt[2] += 2;
        ans += 2;
    }
    if(cnt[0] == 2 && cnt[2] >= 2) {
        cnt[0] = 0; cnt[2] -= 2;
        cnt[3] += 2;
        ans += 2;
    }
    if(cnt[0] == 1 && cnt[3] >= 2) {
        cnt[0] = 0; cnt[3] -= 2;
        cnt[2] += 2;
        ans += 2;
    }
    if(cnt[1] == 1 && cnt[3] > 0) {
        cnt[1] = 0; cnt[3] -= 1;
        cnt[2] += 2;
        ans += 1;
    }
    if(cnt[1] == 1 && cnt[2] >= 2) {
        cnt[1] = 0; cnt[2] -= 2;
        cnt[3] += 2;
        ans += 2;
    }
    if(cnt[1] == 2) {
        cnt[3] += 1;
        cnt[1] -= 2;
        ans += 2;
    }

    if(cnt[0] != 0 || cnt[1] != 0) {
        ans = -1;
    }

    cout << ans << endl;
}