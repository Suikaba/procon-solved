#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> left(n, vector<int>(n + 1)), right(n, vector<int>(n + 1));
    int inv = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            left[i][j + 1] = a[i] < a[j];
        }
        for(int j = i + 1; j < n; ++j) {
            right[i][j + 1] = a[i] > a[j];
        }
        for(int j = 0; j < n; ++j) {
            left[i][j + 1] += left[i][j];
            right[i][j + 1] += right[i][j];
        }
        inv += left[i].back() + right[i].back();
    }

    int ans = inv, cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            const int dec1 = 4 * (right[i][j] - right[i][i]) + 2 * (i - j) + (a[i] > a[j]);
            const int dec2 = 4 * (left[j][j] - left[j][i]) + 2 * (i - j) + (a[i] > a[j]);
            if(ans > inv - dec1 - dec2) {
                ans = inv - dec1 - dec2;
                cnt = 1;
            } else if(ans == inv - dec1 - dec2) {
                cnt += 1;
            }
        }
    }
    ans /= 2;

    cout << ans << ' ' << cnt << endl;
}
