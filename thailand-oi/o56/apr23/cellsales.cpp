#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 1e5 + 5;

int n, ans;
vector<int> coord;
vector<iii> V;
set<int> t[N];

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

void update(int x, int k) {
    for (int i = x; i; i -= i & -i)
        t[i].emplace(k);
}

int query(int x, int k) {
    int ret = 0;
    for (int i = x; i <= coord.size(); i += i & -i) {
        auto it = t[i].lower_bound(k);
        if (it != t[i].end())
            ret |= 1;
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b, c; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        V.emplace_back(a, b, c);
        coord.emplace_back(b);
    }
    sort(V.begin(), V.end(), greater<iii>());
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for (iii v : V) {
        int a, b, c;
        tie(a, b, c) = v;
        if (query(get(b), c))
            ++ans;
        update(get(b), c);
    }
    printf("%d\n", ans);

    return 0;
}