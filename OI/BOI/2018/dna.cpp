#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, k, r;
int A[N], mn[N], cnt[N], valid;

int main() {
    scanf("%d %d %d", &n, &k, &r);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    for (int i = 1, a, b; i <= r; i++) {
        scanf("%d %d", &a, &b);
        mn[a] = b;
    }

    int ans = 1e9;
    for (int i = 1, j = 0; i <= n; i++) {
        ++cnt[A[i]];
        if (mn[A[i]] && cnt[A[i]] == mn[A[i]])
            ++valid;
        while (j + 1 < i) {
            if (cnt[A[j + 1]] - 1 < mn[A[j + 1]])
                break;
            --cnt[A[++j]];
        }
        if (valid == r)
            ans = min(ans, i - j);
    }
    if (ans == 1e9)
        printf("impossible\n");
    else
        printf("%d\n", ans);

    return 0;
}