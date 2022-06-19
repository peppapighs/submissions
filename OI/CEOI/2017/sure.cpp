#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
priority_queue<double> Q1, Q2;

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        double a, b;
        scanf("%lf %lf", &a, &b);
        Q1.emplace(a), Q2.emplace(b);
    }
    double ans = 0, a = 0, b = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (a < b) {
            if (Q1.empty())
                break;
            a += Q1.top();
            Q1.pop();
        } else {
            if (Q2.empty())
                break;
            b += Q2.top();
            Q2.pop();
        }
        ans = max(ans, min(a, b) - i);
    }
    printf("%.4lf\n", ans);

    return 0;
}