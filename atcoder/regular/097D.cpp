#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, ans;
int pos[N], dsu[N];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

int main() {
    iota(dsu, dsu + N, 0);
    scanf("%d %d", &n, &m);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        pos[a] = i;
    }
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        dsu[find(a)] = find(b);
    }
    for (int i = 1; i <= n; i++)
        if (find(pos[i]) == find(i))
            ++ans;
    printf("%d\n", ans);

    return 0;
}