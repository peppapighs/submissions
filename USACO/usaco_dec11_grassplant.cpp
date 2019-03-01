#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<17;

#define var int p = 1, int l = 1, int r = n
#define mid (l + r >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

int n, q;
int par[N], dep[N], rot[N], pos[N], spi[N];
long t[N<<1], lz[N<<1];
vector<int> g[N];

void push(var) {
    if(!lz[p]) return;
    t[p] += lz[p] * (r - l + 1);
    if(l != r) lz[p<<1] += lz[p], lz[p<<1|1] += lz[p];
    lz[p] = 0;
}

template<typename T>
void travel(int x, int y, const T &f, var) {
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) return f(p, l, r);
    travel(x, y, f, lb), travel(x, y, f, rb);
    t[p] = t[p<<1] + t[p<<1|1];
}

int dfs(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1;
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p) {
        int z = dfs(v, u);
        sz += z;
        ret = max(ret, pii(z, v));
    }
    spi[u] = ret.y;
    return sz;
}

void hld() {
    for(int i = 1, idx = 0; i <= n; i++) if(spi[par[i]] != i)
        for(int j = i; j != -1; j = spi[j])
            rot[j] = i, pos[j] = ++idx;
}

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a); 
    }
    dfs(1, 1), hld();
    for(int i = 1; i <= q; i++) {
        char T;
        int a, b;
        scanf(" %c %d %d", &T, &a, &b);
        if(T == 'P') {
            while(rot[a] != rot[b]) {
                if(dep[rot[a]] < dep[rot[b]]) swap(a, b);
                travel(pos[rot[a]], pos[a], [&](var) {
                    lz[p]++;
                    push(p, l, r);
                });
                a = par[rot[a]];
            }
            if(dep[a] > dep[b]) swap(a, b);
            travel(pos[a]+1, pos[b], [&](var) {
                lz[p]++;
                push(p, l, r);
            });
        } else {
            long ans = 0;
            while(rot[a] != rot[b]) {
                if(dep[rot[a]] < dep[rot[b]]) swap(a, b);
                travel(pos[rot[a]], pos[a], [&](var) { ans += t[p]; });
                a = par[rot[a]];
            }
            if(dep[a] > dep[b]) swap(a, b);
            travel(pos[a]+1, pos[b], [&](var) { ans += t[p]; });
            printf("%lld\n", ans);
        }
    }

    return 0;
}