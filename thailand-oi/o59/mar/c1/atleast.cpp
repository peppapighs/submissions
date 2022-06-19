#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

struct item {
    int l, r;
    double k;
    item() {}
};

void update(long t[], int x, long k) {
    for (int i = x; i < N; i += i & -i)
        t[i] += k;
}

long query(long t[], int x) {
    long ret = 0;
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int n, q;
long A[N], t[2][N], ans[N];
item Q[N];
vector<long> V;

int main() {
    fill_n(ans, N, -1);
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", A + i), V.emplace_back(i);
    for (int i = 1; i <= q; i++)
        scanf("%d %d %lf", &Q[i].l, &Q[i].r, &Q[i].k);
    vector<pii> B(n + 1, pii(1, n));
    vector<queue<int>> pos(n + 1);
    sort(V.begin(), V.end(),
         [&](const int &a, const int &b) { return A[a] > A[b]; });
    for (int step = 1; step <= n; step <<= 1) {
        memset(t[0], 0, sizeof t[0]), memset(t[1], 0, sizeof t[1]);
        for (int i = 1; i <= q; i++)
            if (B[i].x < B[i].y)
                pos[(B[i].x + B[i].y + 1) >> 1].emplace(i);
        for (int i = 1; i <= n; i++) {
            update(t[0], V[i - 1], 1), update(t[1], V[i - 1], A[V[i - 1]]);
            while (!pos[i].empty()) {
                int now = pos[i].front();
                pos[i].pop();
                long cnt = query(t[0], Q[now].r) - query(t[0], Q[now].l - 1);
                long sum = query(t[1], Q[now].r) - query(t[1], Q[now].l - 1);
                if (!cnt)
                    B[now].x = i + 1;
                else {
                    double avg = (double)sum / (double)cnt;
                    if (Q[now].k <= avg)
                        B[now].x = i, ans[now] = cnt;
                    else
                        B[now].y = i - 1;
                }
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        if (ans[i] == -1)
            printf("-1\n");
        else
            printf("%lld\n", Q[i].r - Q[i].l + 1 - ans[i]);
    }

    return 0;
}
