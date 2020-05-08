#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, d;
vector<int> job[N], ans[N];

bool solve(int mid) {
    queue<pii> Q;
    for(int i = 1; i <= n; i++) ans[i].clear();
    for(int i = 1; i <= n; i++) {
        for(int x : job[i]) Q.emplace(x, i);
        while(!Q.empty() && ans[i].size() < mid) {
            pii now = Q.front(); Q.pop();
            if(now.y + d < i) return false;
            ans[i].emplace_back(now.x);
        } 
    }
    return Q.empty();
}

int main() {
    scanf("%d %d %d", &n, &d, &m);
    for(int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        job[a].emplace_back(i);
    }
    int l = 0, r = (int)1e6;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(solve(mid)) r = mid;
        else l = mid + 1;
    }
    solve(r);
    printf("%d\n", r);
    for(int i = 1; i <= n; i++) {
        for(int x : ans[i]) printf("%d ", x);
        printf("0\n");
    }

    return 0;
}