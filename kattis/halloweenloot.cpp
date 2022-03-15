#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int K = 1 << 14;

int n;
int A[N], B[N], dp[N][K << 1];

int solve(int i, int sum) {
    if(i == n) return abs(sum - K);
    if(~dp[i][sum]) return dp[i][sum];

    dp[i][sum] = min(solve(i + 1, sum + A[i]), solve(i + 1, sum - B[i]));
    return dp[i][sum];
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", A + i);
    for(int i = 0; i < n; i++) scanf("%d", B + i);

    int ans = solve(0, K), sum = K;
    for(int i = 0; i < n; i++) {
        if(solve(i + 1, sum + A[i]) == ans) {
            printf("A");
            sum += A[i];
        } else {
            printf("B");
            sum -= B[i];
        }
    } 
    printf("\n");
    assert(abs(sum - K) == ans);

    return 0;
}