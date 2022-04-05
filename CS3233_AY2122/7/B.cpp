#include <bits/stdc++.h>

using namespace std;

int n, t;
int A[30], dp[1 << 22];

int solve(int mask) {
    if(~dp[mask]) return dp[mask];
    if(__builtin_popcount(mask) < 3)
        return dp[mask] = 0;

    dp[mask] = 0;
    vector<int> now;
    for(int i = mask; i; i -= i & -i)
        now.emplace_back(__builtin_ctz(i & -i));

    dp[mask] = max(dp[mask], solve(mask - (1 << now[0])));
    int ptr = now.size() - 1;
    for(int i = 1; i < now.size() - 1; i++) {
        ptr = max(ptr, i + 1);
        while(ptr - 1 > i && A[now[0]] + A[now[i]] + A[now[ptr - 1]] >= t)
            --ptr;
        if(A[now[0]] + A[now[i]] + A[now[ptr]] < t)
            continue;
        dp[mask] = max(dp[mask], solve(mask - (1 << now[0]) - (1 << now[i]) - (1 << now[ptr])) + 1);
    } 
    return dp[mask];
}

int main() {
    while(scanf("%d %d", &n, &t), n != 0 && t != 0) {
        memset(dp, -1, sizeof dp);

        for(int i = 0; i < n; i++)
            scanf("%d", A + i);
        sort(A, A + n);
        printf("%d\n", solve((1 << n) - 1));
    }

    return 0;
}