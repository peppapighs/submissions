#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m;
vector<int> g[N];

int solve(int u, int mid) {
    int sz = 1;
    vector<int> child;
    for (int v : g[u]) {
        child.emplace_back(solve(v, mid));
        sz += child.back();
    }
    sort(child.begin(), child.end());
    for (int i = 1; i <= (int)child.size() - mid; i++)
        sz -= child[i - 1];
    return sz;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 2, p; i <= n; i++) {
        scanf("%d", &p);
        g[p].emplace_back(i);
    }
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        int ret = solve(1, mid);
        if (ret >= m)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", r);

    return 0;
}