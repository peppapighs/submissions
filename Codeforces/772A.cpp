#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    pair<int, int> dev[n];

    long long check = 0;

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        dev[i] = {a, b};
        check += a;
    }

    if (check <= p) {
        printf("-1");
        return 0;
    }

    double low = 0, high = 1e14;
    double res = 0;
    for (int i = 0; i < 1000; i++) {
        double mid = (low + high) / 2;
        double c = 0;
        for (int j = 0; j < n; j++) {
            c += max(0.0, (mid * dev[j].first) - dev[j].second) / mid;
        }
        if (c <= p) {
            res = mid;
            low = mid;
        } else {
            high = mid;
        }
    }

    printf("%.10lf", res);

    return 0;
}
