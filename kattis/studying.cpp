#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, T;
double a[N], b[N], c[N];
double ans[N];

int main() {
    scanf("%d %d", &n, &T);

    for(int i = 1; i <= n; i++)
        scanf("%lf %lf %lf", a + i, b + i, c + i);

    double l = 1e9, r = 0.0;
    for(int _ = 1; _ <= 100; _++) {
        double mid = (l + r) / 2;
        double sum = 0.0;
        for(int i = 1; i <= n; i++) {
            ans[i] = max(0.0, (mid - b[i]) / (2.0 * a[i]));
            sum += ans[i];
        }
        if(sum <= T) l = mid;
        else r = mid;
    }
    double ret = 0.0;
    for(int i = 1; i <= n; i++)
        ret += a[i] * ans[i] * ans[i] + b[i] * ans[i] + c[i];
    printf("%f\n", ret / n);

    return 0;
}