#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, l, r, k;

void solve() {
    scanf("%d %d %d %d", &n, &l, &r, &k);
    vector<int> vec;
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if (l <= a && a <= r)
            vec.emplace_back(a);
    }
    sort(vec.begin(), vec.end());
    int ans = 0;
    for (int i = 0; i < vec.size(); i++)
        if (vec[i] <= k) {
            k -= vec[i];
            ans = i + 1;
        }
    printf("%d\n", ans);
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}