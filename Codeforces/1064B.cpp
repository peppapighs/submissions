#include <bits/stdc++.h>

using namespace std;

int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", (int)pow(2.0, 1.0 * __builtin_popcount(n)));
    }

    return 0;
}
