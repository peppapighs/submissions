#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
double A[N], all;

int main() {
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", A + i), all += A[i];

    double l = 0, r = 10000;
    for (int step = 1; step <= 50; step++) {
        double mid = (l + r) / 2;
        double sum = A[2] - mid, best = A[2] - mid;
        for (int i = 3; i <= n - 1; i++) {
            if (sum < 0)
                sum = 0;
            sum += A[i] - mid;
            if (sum > best)
                best = sum;
        }
        if (all - n * mid - best <= 0)
            r = mid;
        else
            l = mid;
    }
    printf("%.3f\n", r);

    return 0;
}