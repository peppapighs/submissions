#include <bits/stdc++.h>

#define long long long

using namespace std;

int n, k, l;
int dp[15];
long fact[15], now;

long ncr(int n, int r) {
        long ret = fact[n] / fact[r];
        ret /= fact[n-r];
        return ret;
}

int main() {
        fact[0] = 1;
        for(int i = 1; i <= 12; i++) fact[i] = fact[i-1] * i;
        scanf("%d %d %d", &n, &k, &l);
        for(int i = 1; i <= k; i++) {
                long t = 0;
                for(int j = dp[i-1] + 1; j <= n-k+i; j++) {
                        if(now + t + ncr(n - j, k - i) >= l) {
                                dp[i] = j;
                                now += t;
                                break;
                        }
                        t += ncr(n - j, k - i);
                }
        }
        for(int i = 1; i <= k; i++) printf("%d ", dp[i]);
        printf("\n");
        
        return 0;
}
