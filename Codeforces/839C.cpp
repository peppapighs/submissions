#include <bits/stdc++.h>

using namespace std;

double ans = 0;

void dfs(vector<int> tree[], int n, int p, double d, double s) {
    double edge = 0;
    for (int i = 0; i < tree[n].size(); i++) {
        if (tree[n][i] != p) {
            edge++;
        }
    }
    if (edge) {
        for (int i = 0; i < tree[n].size(); i++) {
            if (tree[n][i] != p) {
                dfs(tree, tree[n][i], n, d + 1, s * edge);
            }
        }
    } else {
        ans += (d / s);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> tree[n];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[--u].push_back(--v);
        tree[v].push_back(u);
    }
    dfs(tree, 0, -1, 0, 1);

    printf("%.10lf", ans);

    return 0;
}
