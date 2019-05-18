#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, sx, sy, ax, ay;
long d1[N], d2[N], sp, d[N];
vector<pii> g[N];
bitset<N> chk;

int main() {
    fill_n(d1, N, 1e18), fill_n(d2, N, 1e18), fill_n(d, N, 1e18);
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    scanf("%d %d %d %d", &sx, &sy, &ax, &ay);

    priority_queue<pii, vector<pii>, greater<pii> > Q;
    Q.emplace(d1[sx] = 0, sx);
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(d1[u.y] != u.x) continue;
        for(pii v : g[u.y]) if(d1[u.y] + v.y < d1[v.x])
            Q.emplace(d1[v.x] = d1[u.y] + v.y, v.x);
    }
    Q.emplace(d2[sy] = 0, sy);
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(d2[u.y] != u.x) continue;
        for(pii v : g[u.y]) if(d2[u.y] + v.y < d2[v.x])
            Q.emplace(d2[v.x] = d2[u.y] + v.y, v.x);
    }
    for(int i = 1; i <= n; i++) if(d1[i] + d2[i] == d1[sy])
        chk[i] = true;

    Q.emplace(d[ax] = 0, ax);
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(d[u.y] != u.x) continue;
        for(pii v : g[u.y]) if(!chk[v.x] && d[u.y] + v.y < d[v.x])
            Q.emplace(d[v.x] = d[u.y] + v.y, v.x);
    } 
    if(d[ay] == 1e18) printf("-1\n");
    else printf("%lld\n", d[ay]);

    return 0;
}