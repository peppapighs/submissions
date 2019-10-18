#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1 << 17;

vector<int> coord;
pii t[N << 1];

long f(long x, pii l) { return l.x * x + l.y; }

void add(pii k, int p = 1, int l = 1, int r = coord.size()) {
    int m = (l + r) >> 1;
    int L = coord[l-1], M = coord[m-1], R = coord[r-1];
    bool lef = f(L, k) < f(L, t[p]);
    bool mid = f(M, k) < f(M, t[p]);
    if(mid) swap(k, t[p]);
    if(l == r) return;
    else if(lef != mid) add(k, p<<1, l, m);
    else add(k, p<<1|1, m+1, r);
}

long get(long x, int p = 1, int l = 1, int r = coord.size()) {
    if(l == r) return f(x, t[p]);
    int m = (l + r) >> 1;
    int L = coord[l-1], M = coord[m-1], R = coord[r-1];
    if(x <= M) return min(f(x, t[p]), get(x, p<<1, l, m));
    else return min(f(x, t[p]), get(x, p<<1|1, m+1, r));
}

int n;
long h[N], w[N], dp[N];

int main() {
    fill_n(t, N<<1, pii(1e12, 1e12));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", h+i);
        coord.emplace_back(h[i]);
    }
    for(int i = 1; i <= n; i++) {
        scanf("%lld", w+i);
        w[i] += w[i-1];
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    add(pii(-2ll * h[1], h[1] * h[1] - w[1]));
    for(int i = 2; i <= n; i++) {
        dp[i] = get(h[i]) + h[i] * h[i] + w[i-1];
        add(pii(-2ll * h[i], h[i] * h[i] - w[i] + dp[i]));
    }
    printf("%lld\n", dp[n]);

    return 0;
}