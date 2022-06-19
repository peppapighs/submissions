#include <bits/stdc++.h>

using namespace std;

int n;
vector<long long> p;
map<long long, int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n * 2; i++) {
        long long a;
        scanf("%lld", &a);
        p.emplace_back(a);
        mp[a]++;
        if (mp[a] >= n)
            printf("0"), exit(0);
    }
    sort(p.begin(), p.end());
    long long dx = p[n - 1] - p[0];
    long long dy = p[2 * n - 1] - p[n];
    long long ans = dx * dy;
    long long z = p[2 * n - 1] - p[0];
    for (int i = n; i < 2 * n - 1; i++) {
        ans = min(ans, z * (p[i] - p[i - n + 1]));
    }

    printf("%lld", ans);

    return 0;
}