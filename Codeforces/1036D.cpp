#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, m;
long long A[N], B[N];
long long sum;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &A[i]), sum += A[i];
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%lld", &B[i]), sum -= B[i];
    if (sum)
        return !printf("-1\n");
    int c1 = 1, c2 = 1, ans = 1;
    long long s1 = A[1], s2 = B[1];
    while (c1 <= n && c2 <= m) {
        if (s1 == s2)
            ++c1, ++c2, s1 = A[c1], s2 = B[c2], ans++;
        else if (s1 < s2)
            ++c1, s1 += A[c1];
        else
            ++c2, s2 += B[c2];
    }
    --ans;
    printf("%d\n", ans);

    return 0;
}