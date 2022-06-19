#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;

int n;
int A[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", A + i);
        sort(A, A + n, greater<int>());
        for (int i = 0; i < n; i++) {
            bool ok = true;
            for (int j = 0; j < n; j++)
                if (j != i)
                    ok &= (__gcd(A[i], A[j]) == 1);
            if (ok) {
                printf("%d\n", A[i]);
                break;
            }
        }
    }

    return 0;
}