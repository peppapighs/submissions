#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 20;

int n, k, m;
int chk[N + 5], cnt;

int main() {
    scanf("%d %d", &k, &m);
    n = 1 << k;
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        int x = b + 1, y = x + (1 << a) - 1;
        cnt += 2 - chk[x] - chk[y + 1];
        chk[x] = true, chk[y + 1] = true;
        if (cnt == n + 1)
            return !printf("%d\n", i);
    }

    return 0;
}