#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, A[N][N];

void solve(int idx) {
    scanf("%d", &n);
    int trace = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
        scanf("%d", &A[i][j]);
        if(i == j) trace += A[i][j];
    }
    int r = 0, c = 0;
    for(int i = 1; i <= n; i++) {
        set<int> S1, S2;
        for(int j = 1; j <= n; j++) {
            S1.emplace(A[i][j]);
            S2.emplace(A[j][i]);
        }
        if((int)S1.size() != n) ++r;
        if((int)S2.size() != n) ++c;
    }
    printf("Case #%d: %d %d %d\n", idx, trace, r, c);
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}