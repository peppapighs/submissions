#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, a[N], pos[N], mx[N], mn[N];

int main() {
    iota(pos, pos + N, 0);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(pos + 1, pos + n + 1,
         [&](const int &x, const int &y) { return a[x] < a[y]; });
    mn[n + 1] = 1e9 + 1;
    for (int i = n; i; i--) {
        mx[i] = max(pos[i], mx[i + 1]);
        mn[i] = min(pos[i], mn[i + 1]);
    }
    int ans = INT_MAX;
    for (int i = 1; i < n; i++) {
        ans = min(ans, a[pos[i]] / abs(pos[i] - mx[i + 1]));
        ans = min(ans, a[pos[i]] / abs(pos[i] - mn[i + 1]));
    }
    printf("%d\n", ans);

    return 0;
}