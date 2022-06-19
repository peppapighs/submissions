#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

long x1, x2, p1, p2;

void solve() {
    scanf("%lld %lld %lld %lld", &x1, &p1, &x2, &p2);
    long mn = min(p1, p2);
    p1 -= mn, p2 -= mn;
    if (p1 > 10)
        printf(">\n");
    else if (p2 > 10)
        printf("<\n");
    else {
        while (p1--)
            x1 *= 10;
        while (p2--)
            x2 *= 10;
        if (x1 < x2)
            printf("<\n");
        else if (x1 > x2)
            printf(">\n");
        else
            printf("=\n");
    }
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}