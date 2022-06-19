#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, b;
int A[N];

int main() {
    scanf("%d %d", &n, &b);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    int l = 0, r = 5e6;
    while (l < r) {
        int m = (l + r) >> 1;
        int sum = 0;
        for (int i = 1; i <= n; i++)
            sum += (int)(ceil(1.0 * A[i] / m));
        if (sum <= b)
            r = m;
        else
            l = m + 1;
    }
    printf("%d\n", r);

    return 0;
}
