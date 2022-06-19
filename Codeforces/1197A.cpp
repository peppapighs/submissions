#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int T, n;

int main() {
    scanf("%d", &T);
    while (T--) {
        int m1 = -1, m2 = -1;
        scanf("%d", &n);
        for (int i = 1, a; i <= n; i++) {
            scanf("%d", &a);
            if (a > m1)
                swap(a, m1);
            if (a > m2)
                swap(a, m2);
        }
        if (n <= 2)
            printf("0\n");
        else
            printf("%d\n", min(m2 - 1, n - 2));
    }

    return 0;
}