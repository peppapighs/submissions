#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;

int n, k, sum;
int A[N], mn = INT_MAX;
long dp[N];
int cnt;
vector<int> V;

int main() {
        scanf("%d %d", &n, &k);
        for(int i = 1; i <= n; i++) scanf("%d", A+i), mn = min(mn, A[i]);
        for(int i = 1; i <= n; i++) V.emplace_back(A[i] - mn), sum += A[i] - mn;
        if(!sum) return !printf("0\n");
        sort(V.begin(), V.end());
        int mx = V[V.size()-1];
        for(int i = 1; i <= mx+1; i++) {
                int x = lower_bound(V.begin(), V.end(), i) - V.begin();
                dp[i] = n-x;
        }
        long cnt = 0, ans = 1;
        for(int i = 1; i <= mx+1; i++) {
                if(cnt + dp[i] > k) cnt = 0, ++ans;
                cnt += dp[i];
        }
        printf("%lld\n", ans);

        return 0;
}
