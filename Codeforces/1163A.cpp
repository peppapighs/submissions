#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int n, m, cc;
int a[N];

int main() {
    scanf("%d %d", &n, &m);
    if (!m)
        return !printf("1\n");
    for (int i = 1; i < n && m; i += 2)
        --m, ++cc;
    if (n & 1)
        --m;
    if (m > 0)
        cc -= m;
    printf("%d\n", cc);

    return 0;
}