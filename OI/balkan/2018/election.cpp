#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 19;

class SegmentTree {
private:
    int t[N << 1], lz[N << 1];

    void push(int p, int l, int r) {
        if(lz[p]) {
            t[p] += lz[p];
            if(l != r) lz[p << 1] += lz[p], lz[p << 1 | 1] += lz[p];
            lz[p] = 0;
        }
    }
    template<typename T>
    void travel(int x, int y, const T &f, int p = 1, int l = 0, int r = N - 1) {
        push(p, l, r);
        if(x > r || l > y) return;
        if(x <= l && r <= y) return f(p, l, r);
        int mid = (l + r) >> 1;
        travel(x, y, f, p << 1, l, mid), travel(x, y, f, p << 1 | 1, mid + 1, r);
        t[p] = min(t[p << 1], t[p << 1 | 1]);
    }
public:
    void update(int x, int y, int k) {
        travel(x, y, [&](int p, int l, int r) { lz[p] += k, push(p, l, r); });
    }
    int query(int x, int y, int ret = 1e9) {
        travel(x, y, [&](int p, int l, int r) { ret = min(ret, t[p]); });
        return ret;
    }
} tree;

int n, q, ans[N];
char S[N];
vector<pii> Q[N];

int main() {
    scanf("%d %s %d", &n, S + 1, &q);
    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        Q[b].emplace_back(a, i);
    }
    vector<int> stk;
    for(int i = 1; i <= n; i++) {
        if(S[i] == 'C') {
            if(!stk.empty()) tree.update(stk.back(), n, -1), stk.pop_back();
            tree.update(i, n, 1);
        } else stk.emplace_back(i);
        for(pii p : Q[i]) {
            int lhs = min(0, tree.query(p.x, i) - tree.query(p.x - 1, p.x - 1));
            int rhs = (int)stk.size() - (lower_bound(stk.begin(), stk.end(), p.x) - stk.begin());
            ans[p.y] = rhs - lhs;
        }
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);

    return 0;
}