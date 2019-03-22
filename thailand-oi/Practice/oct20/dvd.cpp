#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<17;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int n, k;
int now[N];
pii dp[N], hpow[N], iden(69, 6969);
pii t[N<<1];

void update(int x, int k) { for(t[x += n] = hpow[k]; x != 1; x >>= 1) t[x>>1] = add(t[x], t[x^1]); }

pii query(int l, int r) {
        pii ret(0, 0);
        for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
                if(l & 1) ret = add(ret, t[l++]);
                if(r & 1) ret = add(ret, t[--r]);
        }
        return ret;
}

int main() {
        scanf("%d %d", &n, &k);

        hpow[0] = dp[0] = t[n] = pii(1, 1);
        for(int i = 1; i < n; i++) {
                hpow[i] = mul(hpow[i-1], iden);
                dp[i] = add(dp[i-1], hpow[i]);
                now[i] = i, t[n + i] = hpow[i]; 
        }
        
        for(int i = n-1; i; --i) t[i] = add(t[i<<1], t[i<<1|1]);

        while(k--) {
                int T, a, b;
                scanf("%d %d %d", &T, &a, &b);
                if(T == 0) {
                       swap(now[a], now[b]);
                       update(a, now[a]), update(b, now[b]);
                } else {
                        pii want = dp[b];
                        if(a-1 >= 0) want = sub(want, dp[a-1]);
                        if(query(a, b) == want) printf("YES\n");
                        else printf("NO\n");
                }
        }
        
        return 0;
}
