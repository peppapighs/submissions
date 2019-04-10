#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e3+5;

double slope(pii a, pii b) {
    if(a.x == b.x) return 1e9;
    return (double)(a.y - b.y) / (double)(a.x - b.x);
}

int solve(vector<pii> &V) {
    int sz = V.size();
    vector<pii> line;
    for(int i = 0; i < sz; i++) for(int j = 0; j < i; j++) {
         if(slope(V[i], V[j]) < 0) continue;
         line.emplace_back(i, j);
    }
    sort(line.begin(), line.end(), [&](const pii &a, const pii &b) {
        double m1 = slope(V[a.x], V[a.y]);
        double m2 = slope(V[b.x], V[b.y]);
        return m1 > m2;
    });
    int dp[N];
    memset(dp, -1, sizeof dp);
    dp[0] = 1;
    for(pii l : line) if(dp[l.y] != -1) dp[l.x] = max(dp[l.x], dp[l.y] + 1);
    return dp[sz-1] - 2;
}

int A, n, diag;
vector<pii> hi, lo;

int main() {
    scanf("%d %d", &A, &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        if(a == b) ++diag;
        else if(a < b) hi.emplace_back(a, b);
        else lo.emplace_back(A-a, A-b);
    }
    hi.emplace_back(0, 0), hi.emplace_back(A, A);
    lo.emplace_back(0, 0), lo.emplace_back(A, A);
    sort(hi.begin(), hi.end()), sort(lo.begin(), lo.end());
    int high = solve(hi), low = solve(lo);
    printf("%d\n", max({high + low, high + diag, diag + low}));

    return 0;
}
