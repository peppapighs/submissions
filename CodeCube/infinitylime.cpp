#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 7e5+5;

int m, k, ans[N];
vector<int> coord;
vector<pii> Q;

int main() {
    scanf("%d %d", &m, &k);
    for(int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        coord.emplace_back(a);
    }
    for(int i = 1, a; i <= k; i++) {
        scanf("%d", &a);
        Q.emplace_back(a, i);
    }
    sort(coord.begin(), coord.end());
    sort(Q.begin(), Q.end());
    for(int i = 0, ptr = 0; i < k; i++) {
        while(ptr < m && coord[ptr] - ptr <= Q[i].x) ++ptr;
        ans[Q[i].y] = Q[i].x + ptr;
    }
    for(int i = 1; i <= k; i++) printf("%d ", ans[i]);
    printf("\n");

    return 0;
}