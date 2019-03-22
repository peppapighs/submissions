#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int f(char x) { return x - 'a'; }

int n, q, dp[505];
char A[N], S[505];
vector<int> pos[26];

int main() {
    scanf("%d %d %s", &n, &q, A+1);
    for(int i = 1; i <= n; i++) pos[f(A[i])].emplace_back(i);
    for(int t = 1; t <= q; t++) {
        fill_n(dp, 505, 1e9);
        scanf(" %s", S+1);
        int z = strlen(S+1);
        for(int i = 1; i <= z; i++) {
            for(int j = i; j > 1; j--) {
                if(dp[j-1] == 1e9 || pos[f(S[i])].empty()) continue;
                auto it = upper_bound(pos[f(S[i])].begin(), pos[f(S[i])].end(), dp[j-1]);
                if(it != pos[f(S[i])].end()) dp[j] = min(dp[j], *it);
            }
            if(!pos[f(S[i])].empty()) dp[1] = min(dp[1], pos[f(S[i])][0]);
        }
        int ans = 0;
        for(int i = 1; i <= z; i++) if(dp[i] != 1e9) ans = i;
        printf("%d\n", ans);
    }

    return 0;
}
