#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n;
int A[N], B[N], d[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", A + i, B + i);
        d[i] = A[i] - B[i];
    }
    for (int step = 1; step <= 31; step++)
        for (int i = 1; i <= n; i++) {
            if (d[i] <= 0)
                continue;
            int a = (d[i] + 1) / 2, b = A[i] / 2;
            if (2 * a > A[i])
                swap(a, b);
            A[i] -= 2 * a, d[i] -= 2 * a;
            if (i == n)
                A[1] += a, d[1] += a;
            else
                A[i + 1] += a, d[i + 1] += a;
        }
    for (int i = 1; i <= n; i++)
        if (A[i] != B[i])
            return !printf("No\n");
    printf("Yes\n");

    return 0;
}