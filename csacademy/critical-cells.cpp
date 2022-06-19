#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, m, k;
int dpl[N], dpr[N], chk[N];
vector<pii> v;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1, a, b; i <= k; i++) {
        scanf("%d %d", &a, &b);
        v.emplace_back(a, b);
    }
    sort(v.begin(), v.end());
    vector<int> lis;
    int ret = 0;
    for (int i = 1; i <= k; i++) {
        if (lis.empty() || lis.back() <= v[i - 1].y) {
            lis.emplace_back(v[i - 1].y);
            dpl[i] = lis.size();
        } else {
            auto it = upper_bound(lis.begin(), lis.end(), v[i - 1].y);
            *it = v[i - 1].y;
            dpl[i] = it - lis.begin() + 1;
        }
        ret = max(ret, (int)lis.size());
    }
    lis.clear();
    for (int i = k; i; i--) {
        if (lis.empty() || lis.back() <= -v[i - 1].y) {
            lis.emplace_back(-v[i - 1].y);
            dpr[i] = lis.size();
        } else {
            auto it = upper_bound(lis.begin(), lis.end(), -v[i - 1].y);
            *it = -v[i - 1].y;
            dpr[i] = it - lis.begin() + 1;
        }
    }
    map<int, int> mp;
    for (int i = 1; i <= k; i++)
        if (dpl[i] + dpr[i] - 1 == ret) {
            chk[i] = true;
            ++mp[dpl[i]];
        }
    int ans = 0;
    for (int i = 1; i <= k; i++)
        if (chk[i] && mp[dpl[i]] == 1)
            ++ans;
    printf("%d\n", ans);

    return 0;
}