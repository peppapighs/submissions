#include "coprobber.h"
#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 505;

int n, ret;
int par[N][N], cnt[N][N], adj[N]; //0 - cop turn, 1 - robber turn
bool chk[2][N][N];
queue<iii> Q;

int start(int _n, bool A[MAX_N][MAX_N]) {
    n = _n;
    memset(par, -1, sizeof par);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) adj[i] += A[i][j];
        Q.emplace(0, i, i), Q.emplace(1, i, i);
        chk[0][i][i] = chk[1][i][i] = true;
    }
    while(!Q.empty()) {
        iii now = Q.front(); Q.pop();
        int T, cop, rob;
        tie(T, cop, rob) = now;

        if(T == 0) {
            for(int i = 0; i < n; i++) if(A[rob][i] && !chk[1][cop][i]) {
                ++cnt[cop][i];
                if(cnt[cop][i] == adj[i]) {
                    chk[1][cop][i] = true;
                    Q.emplace(1, cop, i);
                }
            }
        } else {
            for(int i = 0; i < n; i++) if((A[cop][i] || i == cop) && !chk[0][i][rob]) {
                chk[0][i][rob] = true;
                par[i][rob] = cop;
                Q.emplace(0, i, rob);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        bool valid = true;
        for(int j = 0; j < n; j++) if(i != j && par[i][j] == -1) valid = false;
        if(valid) return ret = i;
    }
    return -1;
}

int nextMove(int R) {
    return ret = par[ret][R];
}
