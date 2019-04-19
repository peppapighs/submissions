#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 6e5+5;

int par[N], sz[N], cnt;
stack<pii> S;
bitset<N> tag;

int find(int u) { while(par[u] != u) u = par[u]; return u; }

void unite(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) {
        if(sz[u] & 1) ++cnt;
        tag[u] = true;
    } else {
        if(sz[u] > sz[v]) swap(u, v);
        par[u] = v, sz[v] += sz[u];
    }
    S.emplace(u, (u == v));
}

void rollback(int x) {
    while((int)S.size() > x) {
        int u = S.top().x, md = S.top().y;
        S.pop();
        if(!md) sz[par[u]] -= sz[u], par[u] = u;
        else {
            if(sz[u] & 1) --cnt;
            tag[u] = false;
        }
    }
}

int n, m;
int op[N<<1], u[N<<1], v[N<<1], o[N<<1];
map<pii, int> mp;

void solve(int l, int r) {
    if(l == r) {
        if(op[l] == 2) {
            if(cnt) printf("no\n");
            else printf("yes\n");
        }
        return;
    }
    int mid = (l + r) >> 1, now = S.size();
    for(int i = mid+1; i <= r; i++) if(o[i] < l && u[i])
        unite(u[i], v[i]);
    solve(l, mid), rollback(now);
    for(int i = l; i <= mid; i++) if(o[i] > r && u[i])
        unite(u[i], v[i]);
    solve(mid+1, r), rollback(now);
}

int main() {
    iota(par, par+N, 0), fill_n(sz, N, 1);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= 2*m; i++) {
        if(i % 2 == 0) {
            op[i] = 2;
            continue;
        }
        scanf("%d %d %d", op+i, u+i, v+i);
        if(u[i] > v[i]) swap(u[i], v[i]);
        pii p(u[i], v[i]);
        if(mp.count(p)) {
            o[i] = mp[p];
            o[o[i]] = i;
            mp.erase(p);
        } else mp[p] = i;
    }
    for(auto it : mp) o[it.y] = 1e9;
    solve(1, 2*m);

    return 0;
}