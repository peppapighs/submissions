#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e6 + 5;
const int M = 1e9 + 7;

class SegmentTree {
private:
    pii t[N << 1];
public:
    SegmentTree() {
        fill_n(t, N << 1, pii(-M, -M));
    }

    void update(int x, pii k) {
        for(t[x += N] = k; x != 1; x >>= 1)
            t[x >> 1] = max(t[x], t[x ^ 1]);
    }

    pii query(int l, int r) {
        pii ret(-M, -M);
        for(l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret = max(ret, t[l++]);
            if(r & 1) ret = max(ret, t[--r]);
        }
        return ret;
    }
} t_l, t_r;

int n;
int L[N], R[N], col[N];

void dfs(int u, int c) {
    col[u] = c;
    for(int _ = L[u] + 1; _ <= R[u] - 1; _++) {
        auto [r, v] = t_l.query(L[u] + 1, R[u] - 1);
        if(r > R[u]) {
            t_l.update(L[v], {-M, -M});
            t_r.update(R[v], {-M, -M});
            dfs(v, c ^ 1);
        } else break;
    }
    for(int _ = L[u] + 1; _ <= R[u] - 1; _++) {
        auto [l, v] = t_r.query(L[u] + 1, R[u] - 1);
        if(-l < L[u]) {
            t_l.update(L[v], {-M, -M});
            t_r.update(R[v], {-M, -M});
            dfs(v, c ^ 1);
        } else break;
    }
}

int main() {
    memset(col, -1, sizeof col);

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", L + i, R + i);
        --L[i], --R[i];
        t_l.update(L[i], {R[i], i});
        t_r.update(R[i], {-L[i], i});
    }

    long ans = 1;
    for(int i = 0; i < n; i++) if(col[i] == -1) {
        ans = ans * 2 % M;
        t_l.update(L[i], {-M, -M});
        t_r.update(R[i], {-M, -M});
        dfs(i, 0);
    }

    bool ok = true;
    for(int color = 0; color <= 1; color++) {
        for(int i = 0; i < n; i++) {
            if(col[i] == color) {
                t_l.update(L[i], {R[i], i});
                t_r.update(R[i], {-L[i], i});
            } else {
                t_l.update(L[i], {-M, -M});
                t_r.update(R[i], {-M, -M});
            }
        }
        for(int i = 0; i < n; i++) if(col[i] == color) {
            int r = t_l.query(L[i] + 1, R[i] - 1).x;
            int l = -t_r.query(L[i] + 1, R[i] - 1).x;

            if(r > R[i] || l < L[i]) {
                ok = false;
                break;
            }
        }
    }

    if(ok) printf("%lld\n", ans);
    else printf("0\n");

    return 0;
}