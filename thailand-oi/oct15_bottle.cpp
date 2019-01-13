#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m;
int A[N];
set<pii> S;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", A+i), S.emplace(A[i], i);
    while(m--) {
        vector<int> V;
        int a, ans = 0;
        scanf("%d", &a);
        auto it = S.upper_bound(pii(a, 1e9));
        while(it != S.end()) {
            int pos = it->y;
            V.emplace_back(pos+1), V.emplace_back(pos-1);
            it = S.erase(it), ++ans;
        }
        for(int v : V) {
            auto t = S.find(pii(A[v], v));
            if(t != S.end()) S.erase(t), ++ans;
        }
        printf("%d\n", ans);
    }

    return 0;
}