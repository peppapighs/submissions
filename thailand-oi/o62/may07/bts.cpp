#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1 << 12;
const int M = 505;

int n, m, a, b, k;
int u[M], v[M], c[M];
pii t[N << 1];

void update(int x, int y, int k, int p = 1, int l = 1, int r = n - 1) {
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        t[p].y += k;
        if (t[p].y)
            t[p].x = r - l + 1;
        else if (l != r)
            t[p].x = t[p << 1].x + t[p << 1 | 1].x;
        else
            t[p].x = 0;
        return;
    }
    int mid = (l + r) >> 1;
    update(x, y, k, p << 1, l, mid), update(x, y, k, p << 1 | 1, mid + 1, r);
    if (t[p].y)
        t[p].x = r - l + 1;
    else
        t[p].x = t[p << 1].x + t[p << 1 | 1].x;
}

bool chk(int mid) {
    for (int i = mid; i < n; i++) {
        int cnt = 0;
        for (int j = 1; j <= m; j++)
            if (i - mid + 1 <= u[j] && v[j] <= i + 1)
                ++cnt;
        if (cnt >= k)
            return true;
    }
    return false;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);
    if (a > b)
        swap(a, b);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", u + i, v + i, c + i);
        if (c[i] <= a)
            return !printf("-1\n");
        if (u[i] > v[i])
            swap(u[i], v[i]);
        if (c[i] <= b)
            ++k;
    }
    int l = 1, r = n - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (chk(mid))
            r = mid;
        else
            l = mid + 1;
    }
    int mn = 1e9;
    for (int i = r; i < n; i++) {
        vector<int> V;
        int cnt = 0;
        for (int j = 1; j <= m; j++)
            if (i - r + 1 <= u[j] && v[j] <= i + 1)
                update(u[j], v[j] - 1, 1), V.emplace_back(j), ++cnt;
        if (cnt >= k)
            mn = min(mn, t[1].x);
        for (int j : V)
            update(u[j], v[j] - 1, -1);
    }
    printf("%d\n", a * mn + b * (n - 1 - mn));

    return 0;
}