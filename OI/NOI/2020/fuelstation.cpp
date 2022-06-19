#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1 << 19;

int n, D, pos[N];
long t[N << 1], lz[N << 1];

void push(int p, int l, int r) {
    if (lz[p]) {
        t[p] += lz[p];
        if (l != r) {
            lz[p << 1] += lz[p];
            lz[p << 1 | 1] += lz[p];
        }
        lz[p] = 0;
    }
}

void update(int x, int y, long k, int p = 1, int l = 1, int r = n + 1) {
    push(p, l, r);
    if (x > r || l > y)
        return;
    if (x <= l && r <= y) {
        lz[p] += k, push(p, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    update(x, y, k, p << 1, l, mid), update(x, y, k, p << 1 | 1, mid + 1, r);
    t[p] = max(t[p << 1], t[p << 1 | 1]);
}

int main() {
    iota(pos, pos + N, 0);

    scanf("%d %d", &n, &D);
    vector<iii> vec;
    for (int i = 1, a, b, x; i <= n; i++) {
        scanf("%d %d %d", &x, &a, &b);
        vec.emplace_back(x, a, b);
    }
    vec.emplace_back(D, 0, 1e9);
    sort(vec.begin(), vec.end());
    sort(pos, pos + n + 1,
         [&](int a, int b) { return get<2>(vec[a]) < get<2>(vec[b]); });
    for (int i = 0; i <= n; i++) {
        update(i + 1, i + 1, get<0>(vec[i]));
        update(i + 2, n + 1, -get<1>(vec[i]));
    }
    long ans = 1e18;
    for (int i = 0; i <= n; i++) {
        long now = t[1];
        if (now <= get<2>(vec[pos[i]]))
            ans = min(ans, max(0ll, now));
        update(pos[i] + 1, pos[i] + 1, -get<0>(vec[pos[i]]));
        update(pos[i] + 2, n + 1, get<1>(vec[pos[i]]));
    }
    printf("%lld\n", min(ans, (long)D));

    return 0;
}