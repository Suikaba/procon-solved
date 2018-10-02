// http://codeforces.com/contest/568/problem/B

// �����𖞂����̂́A
// �������̃N���[�N�i���ȕӂ��܂ށj+ ���ȕӂ��܂܂Ȃ�1���_�݂̂���Ȃ�O���t�̏W��
// �ł���B
// �N���[�N�Ɋ܂܂�钸�_���� m �Ƃ���ƁAm �̑I�ѕ��� nCm �ʂ�A�N���[�N�ւ̕������� S(n, 1) + ... + S(n, n) (stirling) �ʂ�
// ����� m = 1, ..., n - 1 �܂ő������킹��Γ����ɂȂ�

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9 + 7;

int main() {
    int n; cin >> n;
    vector<vector<ll>> nCr(n + 1, vector<ll>(n + 1));
    vector<vector<ll>> stir(n + 1, vector<ll>(n + 1));
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(j == 0 || i == j) nCr[i][j] = 1;
            else                 nCr[i][j] = (nCr[i - 1][j] + nCr[i - 1][j - 1]) % mod;
        }
    }
    for(int i = 1; i <= n; ++i) {
        stir[i][1] = stir[i][i] = 1;
        for(int j = 2; j < n; ++j) {
            stir[i][j] = (stir[i - 1][j - 1] + j * stir[i - 1][j]) % mod;
        }
    }

    vector<ll> stir_sum(n + 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            (stir_sum[i] += stir[i][j]) %= mod;
        }
    }

    ll ans = 1;
    for(int i = 1; i < n; ++i) {
        (ans += nCr[n][i] * stir_sum[n - i]) %= mod;
    }

    cout << ans << endl;
}
