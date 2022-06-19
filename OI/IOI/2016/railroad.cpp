#include "railroad.h"
#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 4e5 + 5;

int n;
int qs[N], par[N];
vector<int> coord = {0, (int)2e9};

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

long plan_roller_coaster(vector<int> s, vector<int> t) {
    n = s.size();
    iota(par, par + N, 0);
    for (int i = 0; i < n; i++) {
        coord.emplace_back(s[i]);
        coord.emplace_back(t[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    --qs[get(0)], ++qs[get(2e9)];
    for (int i = 0; i < n; i++) {
        int a = get(s[i]), b = get(t[i]);
        if (s[i] < t[i])
            ++qs[a], --qs[b];
        else
            --qs[b], ++qs[a];
        par[find(a)] = find(b);
    }
    for (int i = 1; i <= coord.size(); i++)
        qs[i] += qs[i - 1];

    long ans = 0;
    vector<pii> E;
    for (int i = 1; i < coord.size(); i++) {
        long d = coord[i] - coord[i - 1];
        if (qs[i] > 0)
            ans += qs[i] * d;
        if (qs[i] != 0)
            par[find(i)] = find(i + 1);
        else
            E.emplace_back(d, i);
    }
    sort(E.begin(), E.end());
    for (pii e : E) {
        long d, i;
        tie(d, i) = e;
        if (find(i) != find(i + 1)) {
            par[find(i)] = find(i + 1);
            ans += d;
        }
    }
    return ans;
}
