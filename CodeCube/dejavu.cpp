#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int n, a[N], len;
int dpl[N], dpr[N], mx[N];
bitset<N> chk;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);

    vector<int> lis;
    for (int i = 1; i <= n; i++) {
        if (lis.empty() || lis.back() <= a[i]) {
            lis.emplace_back(a[i]);
            dpl[i] = lis.size();
        } else {
            auto it = upper_bound(lis.begin(), lis.end(), a[i]);
            *it = a[i];
            dpl[i] = it - lis.begin() + 1;
        }
    }
    len = lis.size();
    lis.clear();
    for (int i = n; i; i--) {
        if (lis.empty() || lis.back() <= -a[i]) {
            lis.emplace_back(-a[i]);
            dpr[i] = lis.size();
        } else {
            auto it = upper_bound(lis.begin(), lis.end(), -a[i]);
            *it = -a[i];
            dpr[i] = it - lis.begin() + 1;
        }
    }
    for (int i = 1; i <= n; i++)
        if (dpl[i] + dpr[i] - 1 == len)
            chk[i] = true;

    long ans = 0, sum = 0;
    for (int i = 1; i <= n; i++)
        if (chk[i]) {
            if (a[i] > mx[dpl[i]]) {
                sum -= mx[dpl[i]];
                sum += (mx[dpl[i]] = a[i]);
            }
            if (dpl[i] == len)
                ans = max(ans, sum);
        }
    printf("%d %lld\n", len, ans);

    return 0;
}