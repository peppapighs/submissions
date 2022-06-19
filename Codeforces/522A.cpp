#include <bits/stdc++.h>

using namespace std;

map<string, int> node;
int mx = 0;

string lower(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < 'a') {
            s[i] = s[i] - 'A' + 'a';
        }
    }
    return s;
}

void dfs(vector<int> tree[], int n, int p, int d) {
    mx = max(mx, d);
    for (int i = 0; i < tree[n].size(); i++) {
        if (tree[n][i] != p) {
            dfs(tree, tree[n][i], n, d + 1);
        }
    }
}

int main() {
    node["polycarp"] = 0;
    int k = 1;
    int n;
    scanf("%d", &n);
    vector<int> tree[n + 1];
    while (n--) {
        string u, v;
        cin >> u >> v >> v;
        u = lower(u);
        v = lower(v);
        if (!node[u] && u != "polycarp") {
            node[u] = k++;
        }
        if (!node[v] && v != "polycarp") {
            node[v] = k++;
        }
        tree[node[v]].push_back(node[u]);
    }
    dfs(tree, 0, -1, 1);
    printf("%d", mx);

    return 0;
}
