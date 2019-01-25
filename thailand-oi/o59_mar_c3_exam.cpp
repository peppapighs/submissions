#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e4+5;

int n, q;
int A[N], t[N], ans[N];
vector<pii> Q[N];
map<int, int> mp;

void update(int x, int k) { for(int i = x; i < N; i += i & -i) t[i] += k; }

int get(int x) {
    int sum = 0;
    for(int i = x; i; i -= i & -i) sum += t[i];
    return sum;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    scanf("%d", &q);
    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        Q[++b].emplace_back(++a, i);
    }
    for(int i = 1; i <= n; i++) {
        if(mp.count(A[i])) update(mp[A[i]], 1);
        mp[A[i]] = i;
        for(pii a : Q[i]) {
            int ret = get(i) - get(a.x-1);
            ans[a.y] = ret;
        }
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);

    return 0;
}