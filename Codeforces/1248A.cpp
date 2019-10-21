#include <bits/stdc++.h>

#define long long long

using namespace std;

int T;

int main() {
    scanf("%d", &T);
    while(T--) {
        int n, m;
        int eve = 0, odd = 0;
        long ans = 0;
        scanf("%d", &n);
        for(int i = 1, a; i <= n; i++) {
            scanf("%d", &a);
            if(a & 1) ++odd;
            else ++eve;
        }
        scanf("%d", &m);
        for(int i = 1, a; i <= m; i++) {
            scanf("%d", &a);
            if(a & 1) ans += odd;
            else ans += eve;
        }
        printf("%lld\n", ans);
    }

    return 0;
}