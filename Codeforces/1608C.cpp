#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n;
int pos[N];
pii A[N];

void solve() {
    priority_queue<pii> Q_bad, Q_good;

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &A[i].x);
        pos[i] = i;
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &A[i].y);
        Q_bad.emplace(A[i].x, A[i].y);
    }
    sort(pos + 1, pos + n + 1, [&](int &a, int &b) {
        return A[a] < A[b];
    });
    int mx_y = 0;
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        int p = pos[i];
        mx_y = max(mx_y, A[p].y);
        while(!Q_bad.empty() && (Q_bad.top().x <= A[p].x || Q_bad.top().y <= mx_y)) {
            Q_good.emplace(Q_bad.top());
            Q_bad.pop();
        }
        if(Q_bad.empty() || (!Q_good.empty() && Q_bad.top().x < Q_good.top().x))
            ans[p] = 1;
        else ans[p] = 0;
    }
    for(int i = 1; i <= n; i++) printf("%d", ans[i]);
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}