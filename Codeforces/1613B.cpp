#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n;
int A[N];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    sort(A + 1, A + n + 1);
    for (int i = 1; i <= n / 2; i++)
        printf("%d %d\n", A[i + 1], A[1]);
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}