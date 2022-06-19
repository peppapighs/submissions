#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

struct trie {
    struct node {
        node *l, *r;
        node() : l(l), r(r) {}
        node(node *l, node *r) : l(l), r(r) {}
    };
    map<int, node *> mp;
    void add(int x, int u, node *p) { mp[u] = update(31, x, p); }
    node *update(int i, int x, node *p) {
        if (i == -1)
            return new node();
        int pos = x >> i & 1;
        if (pos)
            return new node(p ? p->l : NULL, update(i - 1, x, p ? p->r : NULL));
        else
            return new node(update(i - 1, x, p ? p->l : NULL), p ? p->r : NULL);
    }
    int get(int x, int u, int mx) {
        node *now = mp[u];
        int ret = x;
        for (int i = 31; ~i; i--) {
            int pos = x >> i & 1;
            if (pos ^ mx) {
                if (now->r)
                    ret ^= (1 << i), now = now->r;
                else
                    now = now->l;
            } else {
                if (now->l)
                    now = now->l;
                else
                    ret ^= (1 << i), now = now->r;
            }
        }
        return ret;
    }
} T;

int n, q, r, ans;
map<int, vector<int>> g;
map<int, int> K;

void dfs(int u, int p) {
    for (int v : g[u])
        if (v != p) {
            T.add(K[v], v, T.mp[u]);
            dfs(v, u);
        }
}

int main() {
    scanf("%d %d %d", &n, &q, &r);
    scanf("%d", &K[r]);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        scanf("%d", &K[a]);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    T.add(K[r], r, NULL);
    dfs(r, r);
    while (q--) {
        int t, a, b, c;
        scanf("%d %d %d", &t, &a, &b);
        t ^= ans, a ^= ans, b ^= ans;
        if (t == 0) {
            scanf("%d", &c);
            c ^= ans;
            T.add(c, b, T.mp[a]);
        } else {
            int mn = T.get(b, a, 0), mx = T.get(b, a, 1);
            printf("%d %d\n", mn, mx);
            ans = mn ^ mx;
        }
    }

    return 0;
}