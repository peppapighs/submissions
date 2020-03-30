#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int n, dp[N][3][2];
char A[N], B[N];

int solve(int i, int md, int f) {
    if(i == n + 1) return 0;
    int &now = dp[i][md][f];
    if(~now) return now;
    now = 1e9;

    for(int x = 0; x < 3; x++) for(int y = 0; y < 2; y++) {
        int cost = (x != md && x) + (y != f && y);
        int cur = !x ? A[i] - '0' : x - 1;
        if((cur ^ y) == B[i] - '0')
            now = min(now, solve(i + 1, x, y) + cost);
    }
    return now;
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d %s %s", &n, A + 1, B + 1);
    printf("%d\n", solve(1, 0, 0));

    return 0;
}