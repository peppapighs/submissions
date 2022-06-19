#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

int n, q, ans[N];
int A[N], t[N << 1];
map<int, int> M;
vector<pii> Q[N];

void update(int x, int k) {
    for (t[x += N] = k; x != 1; x >>= 1)
        t[x >> 1] = t[x] + t[x ^ 1];
}

int query(int l, int r) {
    int ret = 0;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            ret += t[l++];
        if (r & 1)
            ret += t[--r];
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    scanf("%d", &q);
    for (int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        Q[++b].emplace_back(++a, i);
    }
    for (int i = 1; i <= n; i++) {
        if (M.count(A[i]))
            update(M[A[i]], 1);
        M[A[i]] = i;
        for (pii x : Q[i])
            ans[x.y] = query(x.x, i);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);

    return 0;
}
