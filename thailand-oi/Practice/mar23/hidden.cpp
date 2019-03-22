#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int T, n, suf[N], pos[N];
long dp[N], pwr[N], iden = 98765431;
char S[N];

int main() {
    pwr[0] = 1;
    for(int i = 1; i < N; i++) pwr[i] = pwr[i-1] * iden;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %s", &n, S);
        dp[0] = S[0];
        for(int i = 1; i < n; i++) dp[i] = dp[i-1] * iden + S[i];
        for(int i = 0; i < n; i++) {
            long now = dp[n-1] - dp[i] * pwr[n-i-1];
            now = now * pwr[i+1] + dp[i];
            if(now == dp[n-1]) {
                n = i + 1;
                break;
            }
        }
        for(int i = 0; i < n; i++) suf[i] = i, pos[i] = S[i];
        for(int k = 1; k <= n; k <<= 1) {
            auto chk = [&](int a, int b) {
                if(pos[a] != pos[b]) return pos[a] < pos[b];
                return pos[(a + k) % n] < pos[(b + k) % n];
            };
            sort(suf, suf+n, chk);
            int tmp[N]; tmp[0] = 0;
            for(int i = 0; i < n-1; i++) tmp[i+1] = tmp[i] + chk(suf[i], suf[i+1]); 
            for(int i = 0; i < n; i++) pos[suf[i]] = tmp[i];
        }
        printf("%d\n", suf[0]);
    }

    return 0;
}