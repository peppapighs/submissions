#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second
#define iii tuple<int, int, int>

using namespace std;

const int N = 1e4+5;

int T, n;
int sp[N], par[N], dep[N], hd[N], pos[N];
int t[N<<1];
vector<pii> g[N];

void refresh() {
    memset(sp, 0, sizeof sp);
    memset(dep, 0, sizeof dep);
    memset(par, 0, sizeof par);
    memset(hd, 0, sizeof hd);
    memset(pos, 0, sizeof pos);
    memset(t, 0, sizeof t);
    for(int i = 1; i < N; i++) g[i].clear();
}

int proc(int u, int p) {
    par[u] = p, dep[u] = dep[p] + 1; //Preprocess parent and depth
    int sz = 1; pii ret(0, -1);
    for(pii v : g[u]) if(v.x != p) {
        int z = proc(v.x, u);
        sz += z;
        ret = max(ret, pii(z, v.x));
    }
    sp[u] = ret.y; //Preprocess heavy child for u (-1 for no heavy child)
    return sz;
}

void gen_segt(int u, int p) {
    for(pii v : g[u]) if(v.x != p) {
         t[pos[v.x] + n] = v.y; //Update segment tree
         gen_segt(v.x, u);
    }
}

void gen_hld() {
    proc(1, 1);
    for(int i = 1, idx = 0; i <= n; i++)
        if(sp[par[i]] != i) for(int j = i; j != -1; j = sp[j])
            hd[j] = i, pos[j] = idx++; //Preprocess head of the chain and position in segment tree
    gen_segt(1, 1);
    for(int i = n-1; i; i--) t[i] = max(t[i<<1], t[i<<1|1]); //Build segment tree
}

int query(int l, int r) { //Range max query
    int ret = 0;
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = max(ret, t[l++]);
        if(r & 1) ret = max(ret, t[--r]);
    }
    return ret;
}

void update(int x, int k) { for(t[x += n] = k; x != 1; x >>= 1) t[x>>1] = max(t[x], t[x^1]); } //Update segment tree value

int tquery(int a, int b) { //HLD Jumping function
    int ret = 0;
    while(hd[a] != hd[b]) {
        if(dep[hd[a]] < dep[hd[b]]) swap(a, b);
        ret = max(ret, query(pos[hd[a]], pos[a])); //Walk to the head of the chain and jump to its parent
        a = par[hd[a]];
    }
    if(dep[a] < dep[b]) swap(a, b);
    return max(ret, query(pos[b]+1, pos[a])); //Walk in the same chain
}

int main() {
    scanf("%d", &T);
    while(T--) {
        refresh();
        vector<iii> E;
        scanf("%d", &n);
        for(int i = 1, a, b, c; i < n; i++) {
            scanf("%d %d %d", &a, &b, &c);
            g[a].emplace_back(b, c), g[b].emplace_back(a, c);
            E.emplace_back(a, b, c);
        }
        gen_hld();
        char S[10];
        while(scanf(" %s", S), S[0] != 'D') {
            int a, b;
            scanf("%d %d", &a, &b);
            if(S[0] == 'C') {
                int u, v, w;
                tie(u, v, w) = E[a-1];
                if(par[v] == u) swap(u, v);
                update(pos[u], b);
            } else printf("%d\n", tquery(a, b));
        }
    }

    return 0;
}