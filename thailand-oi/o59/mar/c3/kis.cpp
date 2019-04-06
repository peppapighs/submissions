#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 105;
const long INF = 1e18;

void add(long &a, long b) { a += b; if(a > INF) a = INF; }

int n, l, A[N], pos[N];
long K, dp[N][N];

int main() {
    scanf("%d %d %lld", &n, &l, &K);
    for(int i = 1; i <= n; i++) scanf("%d", A+i), pos[A[i]] = i;
    for(int i = n; i; i--) {
        dp[i][0] = 1;
        for(int j = i+1; j <= n; j++) for(int k = 0; k <= l; k++) {
            if(A[i] < A[j]) add(dp[i][k], dp[j][k]);
            else if(k) add(dp[i][k], dp[j][k-1]);
        }
    }
    int ptr = 0, skip = 0;
    vector<int> ans;
    for(int step = 1; step <= n; step++) {
        bool have = false;
        for(int i = 0; i < n; i++) {
            if(pos[i] <= ptr || K < 0) continue;
            long now = 0;
            for(int j = 0; j <= l - skip - (i < A[ptr]); j++) add(now, dp[pos[i]][j]);
            if(K < now) {
                ans.emplace_back(i);
                if(i < A[ptr]) ++skip;
                ptr = pos[i], --K;
                have = true;
                break; 
            } else K -= now;
        }
        if(!have) break;
    }
    if(ans.empty()) printf("-1");
    else for(int i : ans) printf("%d ", i);
    printf("\n");

    return 0;
}
