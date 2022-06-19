#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, k;
vector<int> V;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    int st;
    scanf("%d", &st);
    for (int i = 2, now; i <= m; i++) {
        scanf("%d", &now);
        V.emplace_back(now - st - 1);
        st = now;
    }
    sort(V.begin(), V.end());
    int ans = 0;
    for (int i = 0; i <= (int)V.size() - k; i++)
        ans += V[i];
    printf("%d\n", ans);

    return 0;
}
