#include <bits/stdc++.h>

using namespace std;

int l, n;
vector<double> vec;

int main() {
    scanf("%d %d", &l, &n);
    for (int i = 1, a; i <= n; i++) {
        char c;
        scanf("%d %c", &a, &c);
        vec.emplace_back(a);
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i < n; i += 2)
        vec[i] = 2.0 * l - vec[i];
    sort(vec.begin(), vec.end());

    double mn = 1e9, mx = -1e9;
    for (int i = 0; i < n; i++) {
        vec[i] -= (2.0 * l / (double)n) * (double)i;
        mn = min(mn, vec[i]), mx = max(mx, vec[i]);
    }
    printf("%f\n", (mx - mn) / 2.0);

    return 0;
}