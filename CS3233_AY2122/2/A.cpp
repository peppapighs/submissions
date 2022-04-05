#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k, m;
int par[N], sz[N];

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

void solve() {
    scanf("%d %d %d", &n, &k, &m);	

    for(int i = 1; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
    }

    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        a = find(a), b = find(b);
        if(a == b || sz[a] + sz[b] > k)
            continue;
        if(a > b) swap(a, b);
        par[a] = b;
        sz[b] += sz[a];
    }
    vector<int> ans;
    for(int i = 1; i <= n; i++) if(find(i) == i)
        ans.emplace_back(i);

    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i++) {
        printf("%d", ans[i]);
        if(i != ans.size() - 1) printf(" ");
    }	
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}
