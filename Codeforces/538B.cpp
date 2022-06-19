#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

int n;
pii dp[N];
vector<int> quas;

int get(int a) {
    int ret = 0;
    for (int i = 6; ~i; i--)
        ret = (ret * 10) + ((a >> i) & 1);
    return ret;
}

int main() {
    fill(begin(dp), end(dp), pii(INT_MAX, 0));
    for (int i = 1; i <= (1 << 6); i++)
        dp[get(i)] = pii(1, 0), quas.emplace_back(get(i));
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        for (int q : quas) {
            if (q >= i)
                break;
            dp[i] = min(dp[i], pii(dp[i - q].x + 1, i - q));
        }

    vector<int> ans;
    int c = n;
    while (dp[c].y)
        ans.emplace_back(c - dp[c].y), c = dp[c].y;
    ans.emplace_back(c);
    printf("%d\n", dp[n].x);
    for (int i : ans)
        printf("%d ", i);

    return 0;
}