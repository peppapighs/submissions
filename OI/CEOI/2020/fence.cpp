#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int M = 1e9 + 7;

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

int n;
long w[N], h[N], pref[N], i2, sum;
vector<pii> stk;

int main() {
    i2 = modpow(2, M - 2);

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", h + i);
    for(int i = 1; i <= n; i++) scanf("%lld", w + i), pref[i] = (w[i] + pref[i - 1]) % M;

    long ans = 0;
    stk.emplace_back(0, 0);
    for(int i = 1; i <= n; i++) {
        long cur_ans = (w[i] + 1) * w[i] % M;
        cur_ans = cur_ans * (h[i] + 1) % M * h[i] % M;
        cur_ans = cur_ans * i2 % M * i2 % M;

        while(!stk.empty() && stk.back().y > h[i]) {
            pii now = stk.back(); stk.pop_back();
            sum -= (pref[now.x] - pref[stk.back().x] + M) % M * (now.y + 1) % M * now.y % M;
            sum = (sum + M) % M;
        }
        
        sum += (pref[i] - pref[stk.back().x] + M) % M * (h[i] + 1) % M * h[i] % M;
        sum %= M;
        stk.emplace_back(i, h[i]);

        cur_ans = (cur_ans + (sum - (w[i] * (h[i] + 1) % M * h[i] % M) + M) % M * w[i] % M * i2 % M) % M;

        ans = (ans + cur_ans + M) % M;
    }
    printf("%lld\n", ans);

    return 0;
}