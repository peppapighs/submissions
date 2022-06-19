#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, A[N], pre[N], suf[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    for (int i = 1, mx = -1; i <= n; i++) {
        if (A[i] <= mx)
            continue;
        mx = max(mx, A[i]);
        for (int j = 0; i + j * j + 1 <= n; j++)
            pre[i + j * j + 1] = max(pre[i + j * j + 1], A[i] + j + 1);
    }
    for (int i = n, mx = -1; i; i--) {
        if (A[i] <= mx)
            continue;
        mx = max(mx, A[i]);
        for (int j = 0; i - j * j - 1 > 0; j++)
            suf[i - j * j - 1] = max(suf[i - j * j - 1], A[i] + j + 1);
    }
    for (int i = 1; i <= n; i++)
        pre[i] = max(pre[i], pre[i - 1]);
    for (int i = n; i; i--)
        suf[i] = max(suf[i], suf[i + 1]);
    for (int i = 1; i <= n; i++)
        printf("%d\n", max(0, max(pre[i], suf[i]) - A[i]));

    return 0;
}