#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int B = 320;

int n, m, q;
int R[N][B], ans[N][B], L[N];
vector<int> rope[N], stk[B];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        rope[a].emplace_back(b);
        L[b] = a;
    }
    for (int i = 1; i <= n; i++) {
        rope[i].emplace_back(i);
        sort(rope[i].begin(), rope[i].end());
        for (int j = 1, ptr = 0; j < B; j++) {
            while (ptr + 1 < rope[i].size() && rope[i][ptr + 1] <= j * B)
                ++ptr;
            R[i][j] = rope[i][ptr];
        }
    }
    for (int i = n; i; i--)
        for (int j = 1; j < B; j++) {
            ans[i][j] = R[i][j];
            while (!stk[j].empty() && stk[j].back() <= R[i][j]) {
                ans[i][j] = max(ans[i][j], ans[stk[j].back()][j]);
                stk[j].pop_back();
            }
            stk[j].emplace_back(i);
        }
    scanf("%d", &q);
    for (int i = 1, l, r; i <= q; i++) {
        scanf("%d %d", &l, &r);
        if (r - l <= B) {
            int now = l;
            for (int j = l + 1; j <= r; j++)
                if (L[j] <= now && L[j] >= l)
                    now = j;
            printf("%d\n", now);
        } else {
            int x = r - (r % B), now = ans[l][x / B];
            for (int j = x + 1; j <= r; j++)
                if (L[j] <= now && L[j] >= l)
                    now = j;
            printf("%d\n", now);
        }
    }

    return 0;
}