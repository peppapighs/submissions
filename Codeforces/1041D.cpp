#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, h;
pii seg[N];
int qs[N];

int main() {
    scanf("%d %d", &n, &h);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &seg[i].x, &seg[i].y);
        qs[i] += qs[i - 1] + seg[i].x - seg[i - 1].y;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = i, r = n;
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (qs[m] - qs[i] < h)
                l = m;
            else
                r = m - 1;
        }
        int ret = seg[l].y - seg[i].x + h - qs[l] + qs[i];
        ans = max(ans, ret);
    }
    printf("%d\n", ans);

    return 0;
}
