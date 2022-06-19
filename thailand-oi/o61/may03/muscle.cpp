#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, t[N];
int A[N], ans[N];

void update(int x, int k) {
    for (int i = x; i < N; i += i & -i)
        t[i] += k;
}
int query(int x, int ret = 0) {
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i), update(i, 1);
    for (int i = n; i; i--) {
        int pos = 0, x = i - A[i];
        for (int j = 19; ~j; j--)
            if (pos + (1 << j) <= n && t[pos + (1 << j)] < x)
                x -= t[pos += (1 << j)];
        ans[i] = pos + 1;
        update(pos + 1, -1);
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}
