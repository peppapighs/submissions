#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n, m, A[N];
map<int, set<int> > M;
map<int, multiset<int> > d;

void del(int x) {
    int c = A[x];
    M[c].erase(x);
    auto it = M[c].upper_bound(x);
    if(it != M[c].end()) d[c].erase(d[c].find(*it - x));
    if(it != M[c].begin()) d[c].erase(d[c].find(x - *prev(it)));
    if(it != M[c].end() && it != M[c].begin()) d[c].insert(*it - *prev(it));
}

void add(int x, int c) {
    A[x] = c;
    auto it = M[c].upper_bound(x);
    if(it != M[c].end()) d[c].insert(*it - x);
    if(it != M[c].begin()) d[c].insert(x - *prev(it));
    if(it != M[c].end() && it != M[c].begin()) d[c].erase(d[c].find(*it - *prev(it)));
    M[c].insert(x);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) M[0].emplace(i), d[0].emplace(1);
    long ans = 0;
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        del(a), add(a, b); 
        if(!d[b].empty()) ans += *d[b].begin();
    }
    printf("%lld\n", ans);

    return 0;
}
