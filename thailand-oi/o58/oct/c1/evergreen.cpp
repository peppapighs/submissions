#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;

int n;
long k;
long A[N];

long f(long m) {
    long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (m + 1) * (m + 1);
        if (i == n)
            continue;
        if (A[i + 1] - m <= A[i] + m) {
            long d = A[i] + m - A[i + 1] + m + 1;
            if (d & 1)
                sum -= (d + 1) * (d + 1) / 4;
            else
                sum -= d * (d + 2) / 4;
        }
    }
    return sum;
}

int main() {
    scanf("%d %lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &A[i]);
    sort(A + 1, A + n + 1);
    int l = 0, r = 1e9;
    while (l < r) {
        int m = (l + r) >> 1;
        if (f((long)m) >= k)
            r = m;
        else
            l = m + 1;
    }
    printf("%d\n", r);

    return 0;
}
