#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, q;
vector<int> g[N];
int rot[N], spi[N], pos[N], dep[N], par[N], sz[N], id[N];
bool chk[N], wht[N];
pii t[N<<1];
multiset<int> S[N];

void add(int i, int x) { S[i].emplace(x); }
void del(int i, int x) { auto it = S[i].find(x); S[i].erase(it); }
pii merge(pii a, pii b) { return pii(min(a.x, b.x), min(a.y, b.y)); }

int proc(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1;
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) if(v != p) {
        int z = proc(v, u);
        sz += z;
        ret = max(ret, make_pair(z, v));
    }
    spi[u] = ret.y;
    return sz;
}

void hld() {
    proc(1, 0);
    for(int i = 1, idx = 0, ch = 0; i <= n; i++) if(spi[par[i]] != i) {
        ++ch;
        for(int j = i; j != -1; j = spi[j])
            pos[j] = idx++, rot[j] = i, id[j] = ch, ++sz[ch], t[pos[j] + n] = pii(1e8, 1e8);
    }
    for(int i = n-1; i; i--) t[i] = merge(t[i<<1], t[i<<1|1]);
    for(int i = 1; i <= n; i++) {
        S[i].emplace(1e8);
        if(!chk[id[i]] && par[rot[i]])
            S[par[rot[i]]].emplace(1e8+1), chk[id[i]] = true;
    }
}

void update(int x, pii k) { for(t[x += n] = k; x != 1; x >>= 1) t[x>>1] = merge(t[x], t[x^1]); }

pii tquery(int l, int r) {
    pii ret(1e8, 1e8);
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = merge(ret, t[l++]);
        if(r & 1) ret = merge(ret, t[--r]);
    }
    return ret;
}

void color(int a) {
    if(wht[a]) del(a, 0), add(a, 1e8);
    else del(a, 1e8), add(a, 0);
    wht[a] ^= 1;
    while(a) {
        int nex = par[rot[a]];
        del(nex, tquery(pos[rot[a]], pos[rot[a]] + sz[id[a]] - 1).x + 1);
        update(pos[a], pii(*S[a].begin() + pos[a] - pos[rot[a]], *S[a].begin() + sz[id[a]] - 1 - pos[a] + pos[rot[a]]));
        add(nex, tquery(pos[rot[a]], pos[rot[a]] + sz[id[a]] - 1).x + 1);
        a = par[rot[a]];
    }
}

int query(int a) {
    int ret = 1e8, dist = 0;
    while(a) {
        ret = min(ret, tquery(pos[rot[a]], pos[a]).y + dist - (sz[id[a]] - 1 - pos[a] + pos[rot[a]]));
        ret = min(ret, tquery(pos[a], pos[rot[a]] + sz[id[a]] - 1).x + dist - (pos[a] - pos[rot[a]]));
        dist += dep[a] - dep[par[rot[a]]];
        a = par[rot[a]];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for(int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    hld();
    cin >> q;
    while(q--) {
        int T, a;
        cin >> T >> a;
        if(T == 0) color(a);
        else {
            int ans = query(a);
            if(ans > n) cout << "-1\n";
            else cout << ans << '\n';
        }
    }

    return 0;
}