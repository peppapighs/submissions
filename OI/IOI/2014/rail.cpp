#include "rail.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e3 + 5;
const int M = 1e6 + 5;

int chk[M];
map<pii, int> mp;

int get_dist(int a, int b) {
    if(mp.count(pii(a, b))) return mp[pii(a, b)];
    return mp[pii(a, b)] = getDistance(a, b);
}

void findLocation(int n, int first, int location[], int stype[]) {
    chk[location[0] = first] = stype[0] = 1;

    int mn = 1e9, A = -1;
    for(int i = 1; i < n; i++) if(get_dist(0, i) < mn)
        mn = get_dist(0, i), A = i;
    chk[location[A] = first + get_dist(0, A)] = stype[A] = 2;
    mp[pii(A, 0)] = mp[pii(0, A)];

    vector<int> L, R;
    for(int i = 1; i < n; i++) if(i != A) {
        if(get_dist(0, i) - get_dist(0, A) == get_dist(A, i))
            L.emplace_back(i);
        else R.emplace_back(i);
    }
    sort(L.begin(), L.end(), [&](int a, int b) {
        return get_dist(A, a) < get_dist(A, b);
    });
    sort(R.begin(), R.end(), [&](int a, int b) {
        return get_dist(0, a) < get_dist(0, b);
    });

    int pv = 0;
    for(int i : L) {
        if(chk[location[pv] + (get_dist(A, pv) + get_dist(pv, i) - get_dist(A, i)) / 2] == 1)
            chk[location[i] = location[pv] + get_dist(pv, i)] = stype[i] = 2;
        else chk[location[i] = location[A] - get_dist(A, i)] = stype[i] = 1, pv = i;
    }
    pv = A;
    for(int i : R) {
        if(chk[location[pv] - (get_dist(0, pv) + get_dist(pv, i) - get_dist(0, i)) / 2] == 2)
            chk[location[i] = location[pv] - get_dist(pv, i)] = stype[i] = 1;
        else chk[location[i] = location[0] + get_dist(0, i)] = stype[i] = 2, pv = i;
    }
}
