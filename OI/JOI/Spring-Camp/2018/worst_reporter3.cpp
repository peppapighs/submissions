#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e5+5;

int n, q;
long s[N], t[N];

int cnt(long T, long R) {
    int l = 0, r = n;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(s[mid] * (T / t[mid]) - mid <= R) r = mid;
        else l = mid + 1;
    }
    if(s[r] * (T / t[r]) - r <= R) return n + 1 - r;
    else return 0;
}

int main() {
    scanf("%d %d", &n, &q);
    s[0] = t[0] = 1;
    for(int i = 1, d; i <= n; i++) {
        scanf("%d", &d);
        long k = d / s[i-1] + (d % s[i-1] != 0);
        s[i] = s[i-1] * k, t[i] = t[i-1] * k;
    }
    for(int i = 1, t, l, r; i <= q; i++) {
        scanf("%d %d %d", &t, &l, &r);
        printf("%d\n", cnt(t, r) - cnt(t, l-1));
    }

    return 0;
}