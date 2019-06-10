
// n �� k ��������Ȃ̂ŁAk �F�ȉ��œh����@�͕K�����݂��邱�Ƃ�������B
//�i���Ȃ݂ɁA���������ł�������C�����邪�A���قȂ�ꍇ�͐��藧���Ȃ����Ƃ�����j
//�����̑傫��������Ƃ��Ă����������Ƃ��܂������Ȃ��B
//�����ŁA�ȉ��̃A���S���Y�����l����B
// 1. S �����ׂĂ̒��_����Ȃ�W���Ƃ���
// 2. S ����łȂ��Ȃ�AS �� deg(v) ���ŏ��̂��̂����o���Av �Ƃ���
// 3. �z�� ord �̖����� v ��ǉ�
// 4. v �̗אڒ��_�̎������f�N�������g����
// 5. 2 �ɖ߂�
//���̂Ƃ��Aord[i] �ɂ��Ĉȉ��̕s�Ϗ��������藧�B
//�u���_ ord[i] �́Aj < i �Ȃ�C�ӂ̒��_ ord[j] �ɐF���h���Ă��Ȃ���΁A�ق��͂ǂ̂悤�ɍʐF����Ă��Ă��A����F�œh�邱�Ƃ��ł���v
//�ȉ��A��G�c�ȏؖ��B
//deg(ord[i]) < k �Ȃ�΁A���������D���ɐF���ʂ邱�Ƃ��ł���B
//deg(ord[i]) = k �ƂȂ邱�Ƃ͂Ȃ��B�������藧�Ƃ���� ord[i] �̗אڒ��_�͈�x�� v �Ƃ��đI�΂�Ă��炸�Adeg(u) = k (u �͗אڒ��_) �����藧�B���l�� u �̗אڒ��_���I�΂�Ă��Ȃ�����c�Ƌc�_�������A���ǂ��̒i�K�ł� ord[i] �ȊO�̔C�ӂ̒��_���I�΂�Ă��Ȃ����ƂɂȂ�B���Ȃ킿�AG �͊��S�O���t�ł���Bk ����Ȃ̂ŁAG �͋����̒��_���܂ނ��A����͖����ł���B
//����āA���Ƃ� ord[i] �̋t���ɐF��K���ɓh���Ă����΂��܂������B
//�v�͎��R�ɓh����͌�񂵂ɂ���A�Ƃ������z�ł����Ȃ��B

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    ifstream ifs("kgraph.in");
    int n, m; ifs >> n >> m;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    int k = 0;
    for(int i = 0; i < m; ++i) {
        int a, b; ifs >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
        deg[a] += 1;
        deg[b] += 1;
        k = max({k, deg[a], deg[b]});
    }
    k += k % 2 == 0;

    set<pii> s; // (deg, v)
    vector<int> ord(n);
    for(int v = 0; v < n; ++v) s.emplace(deg[v], v);
    for(int i = 0; i < n; ++i) {
        const int v = s.begin()->second;
        s.erase(s.begin());
        ord[i] = v;
        for(auto to : g[v]) {
            if(s.count(make_pair(deg[to], to))) {
                s.erase(make_pair(deg[to], to));
                deg[to]--;
                s.emplace(deg[to], to);
            }
        }
    }

    vector<int> ans(n, -1);
    for(int i = n - 1; i >= 0; --i) {
        const int v = ord[i];
        vector<bool> used(k + 1);
        for(auto to : g[v]) {
            if(ans[to] == -1) continue;
            used[ans[to]] = true;
        }
        for(int j = 1; j <= k; ++j) {
            if(!used[j]) {
                ans[v] = j;
                break;
            }
        }
    }

    ofstream ofs("kgraph.out");
    ofs << k << '\n';
    for(int i = 0; i < n; ++i) {
        ofs << ans[i] << '\n';
    }
}
