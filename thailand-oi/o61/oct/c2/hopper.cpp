#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e3 + 5;

int n, m;
vector<pii> V;

int g(int a, int b) {
    if (a <= b)
        return b - a;
    else
        return b + n - a;
}

int f(int k) {
    int dp[N];
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (V[j].x < V[i].x && g(V[j].y, V[i].y) <= k)
                dp[i] = max(dp[i], dp[j] + 1);
    int mx = 0;
    for (int i = 0; i < n; i++)
        mx = max(mx, dp[i]);
    return mx;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        V.emplace_back(a, i);
    }
    sort(V.begin(), V.end());
    int l = 0, r = 2 * n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (f(mid) >= m)
            r = mid;
        else
            l = mid + 1;
    }
    cout << r << endl;

    return 0;
}