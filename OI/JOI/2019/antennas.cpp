#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 18;
const int INF = 1e9 + 1;

int n, q;

int mn[N<<1], mx[N<<1], lo[N<<1], hi[N<<1], t[N<<1];

void push(int p, int l, int r) {
    t[p] = max({t[p], hi[p] - mn[p], mx[p] - lo[p]});
    if(l != r) {
        if(mn[p<<1] != INF) {
            lo[p<<1] = min(lo[p<<1], lo[p]);
            hi[p<<1] = max(hi[p<<1], hi[p]);
        }
        if(mn[p<<1|1] != INF) {
            lo[p<<1|1] = min(lo[p<<1|1], lo[p]);
            hi[p<<1|1] = max(hi[p<<1|1], hi[p]);
        } 
    }
    lo[p] = INF, hi[p] = -INF;
}

void tag(int x, int k, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(l == r) {
        if(k == -1) mn[p] = INF, mx[p] = -INF;
        else mn[p] = mx[p] = k;
        return;
    }
    int mid = l + r >> 1;
    if(x <= mid) tag(x, k, p<<1, l, mid);
    else tag(x, k, p<<1|1, mid+1, r);
    mn[p] = min(mn[p<<1], mn[p<<1|1]), mx[p] = max(mx[p<<1], mx[p<<1|1]);
}

void add(int x, int y, int k, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(x > r || l > y || mn[p] == INF) return;
    if(x <= l && r <= y) {
        lo[p] = min(lo[p], k), hi[p] = max(hi[p], k);
        push(p, l, r);
        return;
    }
    int mid = l + r >> 1;
    add(x, y, k, p<<1, l, mid), add(x, y, k, p<<1|1, mid+1, r);
    mn[p] = min(mn[p<<1], mn[p<<1|1]), mx[p] = max(mx[p<<1], mx[p<<1|1]);
    t[p] = max(t[p<<1], t[p<<1|1]);
}

int query(int x, int y, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(x > r || l > y) return -INF;
    if(x <= l && r <= y) return t[p];
    int mid = l + r >> 1;
    return max(query(x, y, p<<1, l, mid), query(x, y, p<<1|1, mid+1, r));
}

int H[N], A[N], B[N], ans[N];
vector<int> in[N], out[N];
vector<pii> Q[N];

int main() {
    fill_n(mn, N<<1, INF), fill_n(mx, N<<1, -INF);
    fill_n(lo, N<<1, INF), fill_n(hi, N<<1, -INF);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d", H+i, A+i, B+i);
        if(i + A[i] <= n) in[i + A[i]].emplace_back(i);
        if(i + B[i] <= n) out[i + B[i]].emplace_back(i);
    }
    scanf("%d", &q);
    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        Q[b].emplace_back(a, i);
    }
    for(int i = 1; i <= n; i++) {
        for(int x : in[i]) tag(x, H[x]);
        add(i - B[i], i - A[i], H[i]);
        for(pii p : Q[i]) ans[p.y] = query(p.x, i);
        for(int x : out[i]) tag(x, -1);
    }
    for(int i = 1; i <= q; i++) {
        if(ans[i] > 0) printf("%d\n", ans[i]);
        else printf("-1\n");
    }

    return 0;
}