
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1382

// ��@

// �����ɂ� DP �̍����������錩���ڂ����Ă���B
// DP ���l����O�ɁA������ώ@����B
// �F�X�����Ȃǂ��čl���Ă݂�ƁA
// - ����ʒu��3��ȏ�h��͍̂œK�ł͂Ȃ�����
// - 2�̋�Ԃ��Ⴄ�F�œh�鎞�A�����݂͌��ɑS�������Ȃ����A�����������������S�ɓ���Ă���
// ���Ƃ��킩��B����2�ڂ��{���ł���B
// �Ⴆ�� [0, 5] �� B �ŁA[2, 7] �� W �œh�鑀����l���Ă݂�΁A����� [0, 1] �� B �łʂ�A[2, 7] �� W �œh�鑀��Ɠ��l�ł���B

// �܂�A�l����K�v������̂́A�����Ԃ���F�œh�����Ƃ��ɁA���̋�Ԃ�ړI�̐F�ɂ���̂ɍŏ����肩���邩�A�Ƃ������Ƃł���B
// ���_�������΁AB �� W �����݂ɂ������i�܂� B �� W �̋��E�j�����Q�Ŋ����Đ؂�グ�����̂��ŏ��萔�ł���B
// �Ⴆ�΁AWWWWWW �� WBWBWB �ɂ������Ƃ���B���ɑS�̂� B �œh���� BBBBBB �Ƃ��悤�B����ƁA��������ړI�̐F�ɂ��邽�߂ɂ́A�Ɨ����Č���� W �̐������h��̂��œK�ł���B���̐����A"WB" �܂��� "BW" �ƂȂ�ʒu�̐��i����Ȃ�A5 �ӏ�����j���Q�Ŋ����Đ؂�グ�����ɓ������B

// �������āADP���l����ɕK�v�ȏ�񂪑������B
// ���A
// dp[i] := i �����ڂ܂ł݂čŏ��萔�͂����炩
// sum[i] := i �܂ł݂āAW �� B �̋��E�͉��񌻂�邩
// �ƒ�`����Bsum �͗ݐϘa�ŗ\�ߌv�Z���Ă����B
// ����ƑJ�ڂ�
// - s[i - 1] == t[i - 1] �̂Ƃ��Fdp[i] = dp[i - 1]
// - s[i - 1] != t[i - 1] �̂Ƃ��F dp[i] = min(dp[j] + ceil((sum[i] - sum[j + 1]) / 2) + 1)  (i - k <= j < i)
// �ƂȂ�B�Q�ڂ̑J�ڂ� +1 ���Ă���̂́A���ڋ�Ԃ� t[i - 1] ��F�œh�鑀��̕��ł���B

// ���̏�Ԃ��� O(nk) �Ȃ̂ŁA����������B�Q�ڂ̑J�ڎ��𐮗������
// - dp[i] = ceil(min((2 * dp[j] + sum[i] - sum[j + 1]) / 2) + 1)  (i - k <= j < i)
// �ƂȂ�Amin �� j �Ɉˑ����Ă��镔���� 2 * dp[j] - sum[j + 1] �����ł��邩��A���̕����������o���āA�K�؂ȃf�[�^�\�� (deque �� segment tree) �ŊǗ�����Ɨǂ��B

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, k; cin >> n >> k;
    string s, t; cin >> s >> t;

    vector<int> sum(n + 1);
    for(int i = 0; i < n; ++i) {
        sum[i + 1] = sum[i] + (i == 0 || t[i - 1] != t[i]);
    }

    vector<int> dp(n + 1);
    deque<pii> deq;
    deq.emplace_back(0, -1);
    for(int i = 1; i <= n; ++i) {
        if(deq.front().first < i - k) deq.pop_front();
        if(s[i - 1] == t[i - 1]) {
            dp[i] = dp[i - 1];
        } else {
            dp[i] = (deq.front().second + sum[i] + 1) / 2 + 1;
        }
        if(i != n) {
            const int added = 2 * dp[i] - sum[i + 1];
            while(!deq.empty() && deq.back().second >= added) deq.pop_back();
            deq.emplace_back(i, added);
        }
    }

    cout << dp[n] << endl;
}