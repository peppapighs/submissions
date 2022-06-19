#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, x;
set<int> mp1, mp2;
int ans = INT_MAX;

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if (mp1.find(a) != mp1.end())
            ans = min(ans, 0);
        if (mp2.find(a) != mp2.end())
            ans = min(ans, 1);
        if (mp2.find(a & x) != mp2.end())
            ans = min(ans, 2);
        if (mp1.find(a & x) != mp1.end())
            ans = min(ans, 1);
        mp1.insert(a);
        mp2.insert(a & x);
    }

    if (ans == INT_MAX)
        printf("-1");
    else
        printf("%d", ans);

    return 0;
}