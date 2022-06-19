#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;

int n, m, ans;
pii F[N];
map<int, int> mp;

int get(pii a, pii b) { return abs(a.x - b.x) + abs(a.y - b.y); }

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &F[i].x, &F[i].y);
    for (int i = 1; i <= m; i++) {
        int a, b, d = INT_MAX;
        scanf("%d %d", &a, &b);
        for (int j = 1; j <= n; j++)
            d = min(d, get(pii(a, b), F[j]));
        mp[d]++;
        ans = max(ans, mp[d]);
    }

    printf("%d\n", ans);

    return 0;
}
