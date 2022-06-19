#include <bits/stdc++.h>

using namespace std;

const int N = 3e5;

struct SegmentTree {
    int t[N << 1];

    void update(int x, int k) {
        for (t[x += N] = k; x != 1; x >>= 1)
            t[x >> 1] = max(t[x], t[x ^ 1]);
    }

    int query(int l, int r) {
        int ret = 0;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = max(ret, t[l++]);
            if (r & 1)
                ret = max(ret, t[--r]);
        }
        return ret;
    }

    int pos(int x) {
        int l = 0, r = N - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (query(1, mid) < x)
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }
} L, R;

int n, q, s, A[N];
vector<int> top10;

void add(int i, int x) {
    A[i] = x;
    if (i < s)
        L.update(s - i, x);
    else
        R.update(i - s, x);
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        add(i, A[i]);
        top10.emplace_back(i);
    }
    sort(top10.begin(), top10.end(), [&](int a, int b) { return A[a] > A[b]; });
    while (top10.size() > 10)
        top10.pop_back();
    L.update(s, 1e9), R.update(n - s + 1, 1e9);

    scanf("%d", &q);
    for (int i = 1, a, b, ptr = n; i <= q; i++) {
        char c;
        scanf(" %c %d", &c, &a);
        if (c == 'E') {
            scanf("%d", &b), --b;

            auto it = find(top10.begin(), top10.end(), a);
            if (it != top10.end())
                top10.erase(it);
            top10.insert(top10.begin() + b, a);

            for (int j = b; ~j; j--)
                add(top10[j], ++ptr);

            while (top10.size() > 10)
                top10.pop_back();
        } else {
            if (a == s)
                printf("0\n");
            else if (a < s)
                printf("%d\n", (s - a) + R.pos(L.query(1, s - a)));
            else
                printf("%d\n", (a - s) + L.pos(R.query(1, a - s)));
        }
    }

    return 0;
}