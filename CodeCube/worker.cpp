#include <bits/stdc++.h>

using namespace std;

int parent(int *dsu, int n) {
    if (dsu[n] == n) {
        return n;
    }
    return parent(dsu, dsu[n]);
}

int main() {
    int n;
    scanf("%d", &n);
    long long t[n], b[n];
    int dsu[n + 1];
    dsu[0] = 0;
    vector<pair<long long, pair<int, int>>> q;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &t[i]);
        dsu[i + 1] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            q.push_back({b[i] + b[j], {i, j}});
        }
    }
    for (int i = 0; i < n; i++) {
        q.push_back({t[i], {i, n}});
    }
    sort(q.begin(), q.end());
    int ec = 0;
    long long ans = 0;
    for (int i = 0; i < q.size(); i++) {
        int pu = parent(dsu, q[i].second.first);
        int pv = parent(dsu, q[i].second.second);

        if (pu != pv) {
            dsu[pu] = pv;
            ans += q[i].first;
            ec++;
        }

        if (ec == n) {
            break;
        }
    }

    printf("%lld", ans);

    return 0;
}
