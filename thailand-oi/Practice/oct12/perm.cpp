#include <bits/stdc++.h>

#define long long long

using namespace std;

int n, k, l;
int dp[15], chk[15];
long fact[15], now;

long npr(int n, int r) { return fact[n] / fact[n - r]; }

int main() {
    fact[0] = 1;
    for (int i = 1; i <= 12; i++)
        fact[i] = fact[i - 1] * i;
    scanf("%d %d %d", &n, &k, &l);
    for (int i = 1; i <= k; i++) {
        long t = 0;
        for (int j = 1; j <= n; j++) {
            if (chk[j])
                continue;
            if (now + t + npr(n - i, k - i) >= l) {
                dp[i] = j;
                chk[j] = true;
                now += t;
                break;
            }
            t += npr(n - i, k - i);
        }
    }
    for (int i = 1; i <= k; i++)
        printf("%d ", dp[i]);
    printf("\n");

    return 0;
}
