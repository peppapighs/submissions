#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 19;

struct item {
    int val, sum, mx;
    item() : val(-1e9), sum(-1e9), mx(-1e9) {}
    item(int val, int sum, int mx) : val(val), sum(sum), mx(mx) {}
    friend item operator+(const item &a, const item &b) {
        item ret;
        ret.val = max(a.val, b.val);
        ret.sum = max(a.sum, b.sum);
        ret.mx = max({a.mx, b.mx, a.sum + b.val});
        return ret;
    }
} t[N << 1];

int n, q;

void update(int x, int k, bool f, int p = 1, int l = 1, int r = n) {
    if(l == r) {
        if(!f) t[p].val = k;
        else t[p].sum = max(t[p].sum, k);
        if(t[p].val != -1e9 && t[p].sum != -1e9) t[p].mx = t[p].val + t[p].sum;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update(x, k, f, p << 1, l, mid);
    else update(x, k, f, p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

item query(int x, int y, int p = 1, int l = 1, int r = n) {
    if(x <= l && r <= y) return t[p];
    int mid = (l + r) >> 1;
    if(y <= mid) return query(x, y, p << 1, l, mid);
    if(x > mid) return query(x, y, p << 1 | 1, mid + 1, r);
    return query(x, y, p << 1, l, mid) + query(x, y, p << 1 | 1, mid + 1, r);
}

int A[N], ans[N];
vector<int> relevant[N];
vector<pii> Q[N];

int main() {
    scanf("%d", &n);
    vector<int> stk;
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        while(!stk.empty() && A[stk.back()] <= A[i]) {
            relevant[stk.back()].emplace_back(i);
            stk.pop_back();
        }
        if(!stk.empty()) relevant[stk.back()].emplace_back(i);
        stk.emplace_back(i);
    }

    scanf("%d", &q);
    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        Q[a].emplace_back(b, i);
    }
    for(int i = n; i; i--) {
        update(i, A[i], 0);
        for(int x : relevant[i]) if(2 * x - i <= n) 
            update(2 * x - i, A[i] + A[x], 1);
        for(pii p : Q[i]) ans[p.y] = query(i, p.x).mx;
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);

    return 0;
}