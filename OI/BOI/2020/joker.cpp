#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, q;
int u[N], v[N], par[N << 1], sz[N << 1], ans[N];
stack<int> S;
bool odd = false;

int find(int x) {
    while(par[x] != x) x = par[x];
    return x;
}

void unite(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return;
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b], par[b] = a;
    S.emplace(b);
}

void rollback(int x) {
    while(S.size() > x) {
        int u = S.top(); S.pop();
        if(u == -1) odd = false;
        else sz[par[u]] -= sz[u], par[u] = u;
    }
}

void add_edge(int a, int b) {
    unite(a, b + n), unite(b, a + n);
    if((find(a) == find(a + n) || find(b) == find(b + n)) && !odd) {
        odd = true;
        S.emplace(-1);
    }
}

void solve(int l, int r, int optl, int optr) {
    if(l > r) return; 

    int mid = (l + r) >> 1, init = S.size();

    for(int i = l; i < mid; i++) add_edge(u[i], v[i]);
    int right = S.size();

    ans[mid] = -1;
    for(int i = optr; i >= max(mid, optl); i--) {
        if(odd) {
            ans[mid] = i;
            break;
        }
        add_edge(u[i], v[i]);
    } 
    if(ans[mid] == -1) ans[mid] = mid - 1;

    rollback(right), add_edge(u[mid], v[mid]);
    solve(mid + 1, r, ans[mid], optr) ;

    rollback(init);
    for(int i = optr; i > ans[mid]; i--) add_edge(u[i], v[i]);
    solve(l, mid - 1, optl, ans[mid]);

    rollback(init);
}

int main() {
    iota(par, par + (N << 1), 0), fill_n(sz, N << 1, 1);

    scanf("%d %d %d", &n, &m, &q);
    for(int i = 1; i <= m; i++) scanf("%d %d", u + i, v + i);

    solve(1, m, 1, m); 

    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        if(b <= ans[a]) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}