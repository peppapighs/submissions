#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, d;
int par[N], sz[N];

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int main() {
    iota(par, par + N, 0);
    fill_n(sz, N, 1);

    scanf("%d %d", &n, &d);
    int excess = 0;
    for (int i = 1, a, b; i <= d; i++) {
        scanf("%d %d", &a, &b);
        if (find(a) == find(b))
            ++excess;
        else {
            a = find(a), b = find(b);
            sz[a] += sz[b];
            par[b] = a;
        }
        vector<int> total_sz;
        for (int j = 1; j <= n; j++)
            if (find(j) == j)
                total_sz.emplace_back(sz[j]);
        sort(total_sz.begin(), total_sz.end(), greater<int>());
        int ans = 0;
        for (int i = 0; i <= min(excess, (int)total_sz.size() - 1); i++)
            ans += total_sz[i];
        printf("%d\n", ans - 1);
    }

    return 0;
}