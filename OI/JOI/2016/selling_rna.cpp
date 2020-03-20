#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

struct SegmentTreeSum {
    int t[N << 1];
    void update(int x, int k) {
        for(t[x += N] += k; x != 1; x >>= 1)
            t[x >> 1] = t[x] + t[x ^ 1];    
    }

    int query(int l, int r) {
        int ret = 0;
        for(l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret += t[l++];
            if(r & 1) ret += t[--r];
        }
        return ret;
    }
} t;

int n, q;
int pos[N], idx[N], a[N], b[N], ans[N];
vector<int> L[N], R[N];
vector<string> S, pre, suf;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    iota(pos, pos + N, 0);
    
    cin >> n >> q;

    S.resize(n), pre.resize(q), suf.resize(q);
    for(int i = 0; i < n; i++) cin >> S[i];
    for(int i = 0; i < q; i++) cin >> pre[i] >> suf[i];

    sort(S.begin(), S.end());
    for(int i = 0; i < q; i++) {
        int l = lower_bound(S.begin(), S.end(), pre[i]) - S.begin();
        ++pre[i].back();
        int r = lower_bound(S.begin(), S.end(), pre[i]) - S.begin();
        L[l].emplace_back(i), R[r].emplace_back(i);
    }

    vector<string> rev;
    for(int i = 0; i < n; i++) {
        reverse(S[i].begin(), S[i].end());
        rev.emplace_back(S[i]);
    }
    sort(rev.begin(), rev.end());
    sort(pos, pos + n, [&](int &a, int &b) { return S[a] < S[b]; });
    for(int i = 0; i < n; i++) idx[pos[i]] = i;

    for(int i = 0; i < q; i++) {
        reverse(suf[i].begin(), suf[i].end());
        a[i] = lower_bound(rev.begin(), rev.end(), suf[i]) - rev.begin();
        ++suf[i].back();
        b[i] = lower_bound(rev.begin(), rev.end(), suf[i]) - rev.begin() - 1;
    }

    for(int i = n - 1; ~i; i--) {
        t.update(idx[i], 1);
        for(int x : L[i]) ans[x] += t.query(a[x], b[x]);
        for(int x : R[i]) ans[x] -= t.query(a[x], b[x]);
    }
    for(int i = 0; i < q; i++) cout << ans[i] << '\n';

    return 0;
}