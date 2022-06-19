#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k, ans, A[N];
vector<int> g[N];

int dfs(int u, int p) {
    int sum = A[u];
    vector<int> vec;
    for (int v : g[u])
        if (v != p)
            vec.emplace_back(dfs(v, u));
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        if (sum + vec[i] > k)
            ++ans;
        else
            sum += vec[i];
    }
    return sum;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(1, 0);
    printf("%d\n", ans);

    return 0;
}