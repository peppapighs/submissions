#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, qs[N];

bool chk(int mid, int a[]) {
    for (int i = 0; i < n; i++)
        qs[i] = 0;
    for (int i = 0; i < n; i++) {
        int l = (i - mid + n) % n;
        int r = (i + mid + n) % n;
        l = (l - a[i] + 1 + n) % n;
        r = (r - a[i] + 1 + n) % n;
        ++qs[l], --qs[r + 1];
        if (l > r)
            ++qs[0], --qs[n];
    }
    for (int i = 1; i < n; i++)
        qs[i] += qs[i - 1];
    for (int i = 0; i < n; i++)
        if (qs[i] == n)
            return true;
    return false;
}

int a[N], ra[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i), ra[n - i - 1] = a[i];

    int l = 0, r = n / 2;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (chk(mid, a) || chk(mid, ra))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", r);

    return 0;
}