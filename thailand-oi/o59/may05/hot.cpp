#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, q, pos[N], d[N], md[N];
int t1[N << 1], t2[N << 1];

void update1(int x, int k) {
    for (t1[x += N] = k; x != 1; x >>= 1)
        t1[x >> 1] = min(t1[x], t1[x ^ 1]);
}
void update2(int x, int k) {
    for (t2[x += N] = k; x != 1; x >>= 1)
        t2[x >> 1] = max(t2[x], t2[x ^ 1]);
}
int qmin(int l, int r, int ret = 1e9) {
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = min(ret, t1[l++]);
        if (r & 1)
            ret = min(ret, t1[--r]);
    }
    return ret;
}
int qmax(int l, int r, int ret = -1) {
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret = max(ret, t2[l++]);
        if (r & 1)
            ret = max(ret, t2[--r]);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", d + i);
    sort(d + 1, d + n + 1);
    for (int t = 1, k; t <= q; t++) {
        int ans = 0;
        scanf("%d", &k);
        vector<int> vec;
        vector<pii> coord;
        fill_n(t1, N << 1, 1e9), fill_n(t2, N << 1, -1);
        for (int i = 1, a; i <= k; i++) {
            scanf("%d", &a);
            vec.emplace_back(a);
        }
        sort(vec.begin(), vec.end());
        for (int i = 1, ptr = 0; i <= n; i++) {
            while (ptr < (int)vec.size() && d[i] >= vec[ptr])
                ++ptr;
            md[i] = 1e9;
            if (ptr != (int)vec.size())
                md[i] = min(md[i], vec[ptr] - d[i]);
            if (ptr)
                md[i] = min(md[i], d[i] - vec[ptr - 1]);
            coord.emplace_back(-(d[i] + md[i]), i);
        }
        sort(coord.begin(), coord.end());
        for (int i = 1; i <= n; i++)
            pos[coord[i - 1].y] = i;
        for (int i = 1, ptr = n; i <= n; i++) {
            while (ptr && md[i] - d[i] <= coord[ptr - 1].x)
                --ptr;
            int a = qmin(0, ptr - 1), b = qmax(ptr, n - 1);
            if (a != 1e9)
                ans = max(ans, d[i] - a);
            if (b != -1)
                ans = max(ans, md[i] + b);
            update1(pos[i] - 1, d[i]), update2(pos[i] - 1, md[i]);
        }
        printf("%d\n", ans);
    }

    return 0;
}
