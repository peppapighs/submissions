#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1<<17;

#define var int p = 1, int l = 1, int r = n
#define mid (l + r >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

int n, L, H[N], W[N];
long t1[N<<1], t2[N<<1], lz[N<<1], dp[N];
vector<int> V;

void push(var) {
    if(!lz[p]) return;
    t2[p] = t1[p] + lz[p];
    if(l != r) lz[p<<1] = lz[p<<1|1] = lz[p];
    lz[p] = 0;
}

void update(int x, long k, var) {
    push(p, l, r);
    if(l == r) return void(t1[p] = k);
    if(x <= mid) update(x, k, lb);
    else update(x, k, rb);
    t1[p] = min(t1[p<<1], t1[p<<1|1]);
    t2[p] = min(t2[p<<1], t2[p<<1|1]);
}

template<typename T>
void travel(int x, int y, const T &f, var) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) return f(p, l, r);
    travel(x, y, f, lb), travel(x, y, f, rb);
    t2[p] = min(t2[p<<1], t2[p<<1|1]);
}

int main() {
    fill_n(t1, N<<1, 1e12), fill_n(t2, N<<1, 1e12);
    scanf("%d %d", &n, &L);
    for(int i = 1; i <= n; i++) scanf("%d %d", H+i, W+i);
    for(int i = 2; i <= n; i++) W[i] += W[i-1];
    V.emplace_back(0), update(1, 0);
    for(int i = 1, j = 1; i <= n; i++) {
        while(V.size() > 1 && H[V.back()] <= H[i]) V.pop_back();
        travel(V.back()+1, i, [&](var) {
            lz[p] = H[i];
            push(p, l, r);
        });
        V.emplace_back(i);
        while(W[i] - W[j-1] > L) j++;
        long now = 1e12;
        travel(j, i, [&](var) { now = min(now, t2[p]); });
        dp[i] =  now;
        update(i+1, now);
    }
    printf("%lld\n", dp[n]);

    return 0;
}