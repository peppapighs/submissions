#include <bits/stdc++.h>

using namespace std;

long long arr[9] = {3LL,      7LL,          31LL,
                    127LL,    8191LL,       131071LL,
                    524287LL, 2147483647LL, 2305843009213693951LL};

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        long long x;
        scanf("%lld", &x);
        bool find = false;
        for (int i = 0; i < 9; i++) {
            if (x == arr[i]) {
                find = true;
            }
        }
        if (find) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}