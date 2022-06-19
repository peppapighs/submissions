#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;

int n, m, k;
long ans;
vector<long> V;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    ans = m - 1;
    for (int i = 1, a, b, c; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        V.emplace_back(a - b - c);
    }
    sort(V.begin(), V.end());
    for (int i = 0; i < k; i++)
        ans += V[i];
    printf("%lld\n", ans);

    return 0;
}
