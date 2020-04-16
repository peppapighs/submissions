#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 205;

int s, m, q;
long dp[N][N][N];

void add(long &a, long b) {
    a += b;
    if(a > 1e18 + 1) a = 1e18 + 1;
}

long solve(int idx, int sum, int md) {
    if(idx == 200) return (sum == s && md == 0);
    long &now = dp[idx][sum][md];
    if(~now) return now;

    now = 0;
    for(int i = 0; i <= 9 && sum + i <= s; i++)
        add(now, solve(idx + 1, sum + i, (md * 10 + i) % m));
    return now;
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d %d %d", &s, &m, &q);
    long k;
    for(int i = 1; i <= q; i++) {
        scanf("%lld", &k), --k;
        deque<int> ans;
        int sum = 0, md = 0;
        bool valid = false;
        while(ans.size() < 200) {
            valid = false;
            for(int i = 0; i <= 9 && sum + i <= s; i++) {
                long now = solve(ans.size() + 1, sum + i, (md * 10 + i) % m);
                if(now <= k) k -= now;
                else {
                    ans.emplace_back(i);
                    sum += i, md = (md * 10 + i) % m;
                    valid = true;
                    break;
                }
            }
            if(!valid) break;
        }
        if(k || !valid) printf("NIE\n");
        else {
            while(ans.size() > 1 && ans.front() == 0) ans.pop_front();
            for(int x : ans) printf("%d", x);
            printf("\n");
        }
    }

    return 0;
}