#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

int n, x, pre[N], suf[N];
long ans;
vector<int> v;
pii pos[N];

bool check(int l, int r) {
    int f = lower_bound(v.begin(), v.end(), l) - v.begin();
    int g = upper_bound(v.begin(), v.end(), r) - v.begin() + 1;
    if (pre[f] && suf[g]) {
        if (g == n + 1 || !f)
            return true;
        else
            return pos[f].y < pos[g].y;
    } else
        return false;
}

int main() {
    scanf("%d %d", &n, &x);
    for (int i = 1, a; i <= n; i++)
        scanf("%d", &a), pos[i] = pii(a, i), v.emplace_back(a);
    sort(v.begin(), v.end()), sort(pos + 1, pos + n + 1);
    pre[0] = pre[1] = suf[n + 1] = suf[n] = true;
    for (int i = 2; i <= n; i++) {
        if (!pre[i - 1])
            pre[i] = 0;
        else
            pre[i] = (pos[i].y > pos[i - 1].y);
    }
    for (int i = n - 1; i; i--) {
        if (!suf[i + 1])
            suf[i] = false;
        else
            suf[i] = (pos[i].y < pos[i + 1].y);
    }
    for (int i = 1; i <= x; i++) {
        int l = i, r = x;
        if (!check(l, x))
            continue;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(i, mid))
                r = mid;
            else
                l = mid + 1;
        }
        ans += x - r + 1;
    }
    printf("%lld\n", ans);

    return 0;
}