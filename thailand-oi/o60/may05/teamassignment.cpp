#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, a, b;
int A[N], dp[N];

bool f(int m) {
    memset(dp, 0, sizeof dp);
    deque<int> pos;
    vector<int> T;
    dp[0] = 1, T.emplace_back(0);
    for (int i = 1; i < a; i++)
        if (A[i] >= m)
            pos.emplace_back(i);
    for (int i = a; i <= n; i++) {
        if (A[i] >= m)
            pos.emplace_back(i);
        if (!pos.empty() && pos.front() == i - b)
            pos.pop_front();
        if (pos.empty())
            continue;

        int last = pos.back(), x = max(0, i - b), y = min(i - a, last - 1);
        int chk = upper_bound(T.begin(), T.end(), y) -
                  lower_bound(T.begin(), T.end(), x);
        if (chk)
            dp[i] = 1, T.emplace_back(i);
    }
    return (bool)dp[n];
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    int l = 0, r = 1e9;
    bool valid = false;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (f(m))
            l = m, valid = true;
        else
            r = m - 1;
    }
    if (valid)
        printf("%d\n", l);
    else
        printf("-1\n");

    return 0;
}