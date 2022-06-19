#include <bits/stdc++.h>

#define ld long double

using namespace std;

const int N = 1e5 + 5;

int n;
int pos[N];
ld a[N], b[N], c[N], t[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    iota(pos, pos + N, 0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i] >> c[i] >> t[i];
    sort(pos + 1, pos + n + 1, [&](int a, int b) { return t[a] > t[b]; });
    ld ca = 0, cb = 0, cc = 0;
    ld ans = 0;
    for (int i = 1; i <= n; i++) {
        ca += a[pos[i]], cb += b[pos[i]], cc += c[pos[i]];
        ld crit = -0.5 * cb / ca;
        ans = max({ans, cc, ca * t[pos[i]] * t[pos[i]] + cb * t[pos[i]] + cc});
        if (0 <= crit && crit <= t[pos[i]])
            ans = max(ans, ca * crit * crit + cb * crit + cc);
    }
    cout << setprecision(18) << fixed << ans << "\n";

    return 0;
}