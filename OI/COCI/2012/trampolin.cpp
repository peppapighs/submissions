#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, k, ans, cnt;
char T[N];
int A[N], dp1[N], dp2[N];
bool chk[N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    scanf(" %s", T + 1);
    for (int i = 1; i <= n; i++)
        if (T[i] == 'T')
            chk[i] = true;

    for (int i = 2; i <= n; i++)
        if (A[i] >= A[i - 1])
            chk[i] |= chk[i - 1];
    for (int i = n - 1; i; i--)
        if (A[i] >= A[i + 1])
            chk[i] |= chk[i + 1];

    for (int i = 1; i <= n; i++)
        if (chk[i])
            ++ans;

    if (!chk[1])
        dp1[1] = 1;
    if (!chk[n])
        dp2[n] = 1;
    for (int i = 2; i <= n; i++) {
        if (!chk[i]) {
            dp1[i] = 1;
            if (A[i] >= A[i - 1])
                dp1[i] += dp1[i - 1];
        }
        cnt = max(cnt, dp1[i]);
    }
    for (int i = n - 1; i; i--) {
        if (!chk[i]) {
            dp2[i] = 1;
            if (A[i] >= A[i + 1])
                dp2[i] += dp2[i + 1];
        }
        cnt = max(cnt, dp2[i]);
    }

    int t1 = 0, t2 = 0;
    for (int i = k + 1; i <= n && A[i] == A[k]; i++)
        ++t1;
    for (int i = k - 1; i && A[i] == A[k]; i--)
        ++t2;

    if (!chk[k])
        printf("%d\n", max(dp1[k] + t1, dp2[k] + t2));
    else
        printf("%d\n", ans + cnt);

    return 0;
}
