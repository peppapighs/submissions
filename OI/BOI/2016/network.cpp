#include "network.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;

map<pii, int> mp;

int get_dist(int a, int b) {
    if (a == b)
        return 0;
    else if (mp.count(pii(a, b)))
        return mp[pii(a, b)];
    else
        return mp[pii(a, b)] = mp[pii(b, a)] = ping(a, b) + 1;
}

int len;
vector<int> dist[N];

void findRoute(int n, int a, int b) {
    for (int i = 1; i <= n; i++)
        if (i != a) {
            int now = get_dist(a, i);
            dist[now].emplace_back(i);
            if (i == b)
                len = now;
        }
    vector<int> ans = {b};
    for (int i = len - 1; i; i--)
        for (int x : dist[i])
            if (get_dist(ans.back(), x) == 1) {
                ans.emplace_back(x);
                break;
            }
    reverse(ans.begin(), ans.end());
    for (int x : ans)
        travelTo(x);
}
