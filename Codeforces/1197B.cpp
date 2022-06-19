#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, mx, idx;
int A[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        if (A[i] > mx)
            mx = A[i], idx = i;
    }
    int l = idx - 1, r = idx + 1, pv = mx;
    while (l != 0 || r != n + 1) {
        if (A[l] > pv || A[r] > pv)
            return !printf("NO\n");
        if (l != 0 && r != n + 1) {
            if (A[l] > A[r])
                pv = A[l--];
            else
                pv = A[r++];
        } else if (l != 0)
            pv = A[l--];
        else
            pv = A[r++];
    }
    printf("YES\n");

    return 0;
}