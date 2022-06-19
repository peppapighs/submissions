#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MAX = 1e6;

struct item {
    int lo, hi;    // Low and High value represented by current node
    vector<int> V; // Left child array
    item *l, *r;   // Pointer to the children
    item(int *al, int *ar, int x, int y) { // Build
        lo = x, hi = y;
        if (lo == hi || al >= ar)
            return;
        int m = (lo + hi) >> 1;
        auto f = [m](int x) { return x <= m; };
        V.emplace_back(0);
        for (auto it = al; it != ar; it++)
            V.emplace_back(V.back() + f(*it));
        auto pv = stable_partition(al, ar, f);
        l = new item(al, pv, x, m), r = new item(pv, ar, m + 1, y);
    }

    int kth(int x, int y, int k) { // kth smallest element in range
        if (lo == hi)
            return lo;
        int left = V[y] - V[x - 1], a = V[x - 1], b = V[y];
        if (k <= left)
            return l->kth(a + 1, b, k);
        else
            return r->kth(x - a, y - b, k - left);
    }

    int
    leqcnt(int x, int y,
           int k) { // Count numbers that are less than or equal to k in range
        int m = (lo + hi) >> 1;
        if (m == k)
            return V[y] - V[x - 1];
        int left = V[y] - V[x - 1], a = V[x - 1], b = V[y];
        if (k <= m)
            return l->leqcnt(a + 1, b, k);
        else
            return left + r->leqcnt(x - a, y - b, k);
    }

    int cnt(int x, int y, int k) { // Count k occurences in range
        if (lo == hi)
            return y - x + 1;
        int m = (lo + hi) >> 1;
        int left = V[y] - V[x - 1], a = V[x - 1], b = V[y];
        if (k <= m)
            return l->cnt(a + 1, b, k);
        else
            return r->cnt(x - a, y - b, k);
    }
};

int n, q;
int A[N];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    item t(A + 1, A + n + 1, 1,
           MAX); // Construct wavelet tree *Note that array after constuction
                 // will be sorted and unusable*
    while (q--) {
        int T;
        int a, b, c;
        scanf("%d %d %d %d", &T, &a, &b, &c);
        if (T == 0)
            printf("%d\n", t.kth(a, b, c));
        else if (T == 1)
            printf("%d\n", t.leqcnt(a, b, c));
        else
            printf("%d\n", t.cnt(a, b, c));
    }

    return 0;
}