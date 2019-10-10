#include "scales.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int tree[] = {0, 116, 116, 116, 22, 23, 22, 16, 17, 16, 10, 11, 10, 103, 109, 4, 102, 108, 4, 102, 108, 5, 97, 109, 4, 96, 108, 4, 96, 108, 5, 97, 103, 4, 96, 102, 4, 96, 102, 5, 44, 5, 18, 44, 5, 18, 5, 11, 17, 19, 3, 17, 19, 3, 11, 3, 32, 26, 19, 16, 3, 19, 10, 3, 3, 68, 62, 45, 5, 12, 50, 5, 12, 11, 5, 17, 13, 3, 23, 13, 3, 11, 30, 3, 26, 13, 22, 3, 13, 10, 3, 66, 3, 62, 46, 5, 6, 52, 5, 6, 11, 11, 5, 7, 3, 23, 7, 3, 17, 24, 24, 3, 7, 22, 3, 7, 16, 3, 60, 60, 3, 82, 5, 82, 9, 3, 14, 82, 16, 44, 81, 5, 81, 15, 8, 3, 10, 81, 44, 1, 8, 8, 63, 14, 32, 69, 8, 26, 3, 3, 27, 27, 4, 32, 46, 44, 4, 3, 3, 33, 33, 26, 4, 45, 44, 4, 1, 29, 29, 29, 47, 5, 29, 47, 5, 3, 3, 63, 82, 80, 5, 63, 5, 68, 3, 3, 69, 81, 80, 5, 69, 62, 5, 1, 42, 42, 43, 26, 4, 43, 26, 4, 82, 5, 82, 3, 9, 15, 82, 22, 45, 80, 5, 80, 8, 14, 3, 10, 80, 45, 12, 63, 30, 8, 1, 8, 62, 8, 29, 3, 3, 27, 4, 27, 33, 46, 45, 4, 3, 3, 32, 26, 32, 4, 45, 44, 4, 5, 53, 29, 29, 1, 29, 53, 29, 5, 3, 3, 63, 82, 81, 5, 5, 63, 69, 3, 3, 68, 81, 80, 5, 62, 68, 5, 4, 26, 49, 48, 1, 48, 26, 49, 4, 81, 5, 81, 3, 9, 8, 81, 22, 46, 80, 5, 80, 9, 3, 8, 16, 80, 46, 6, 63, 35, 63, 6, 35, 14, 14, 1, 3, 3, 26, 4, 27, 26, 46, 45, 4, 3, 3, 26, 27, 4, 26, 46, 44, 4, 5, 59, 35, 59, 5, 35, 35, 35, 1, 3, 3, 62, 82, 81, 5, 5, 63, 62, 3, 3, 62, 82, 80, 5, 63, 5, 62, 4, 32, 55, 32, 4, 55, 54, 54, 1};
vector<vector<int> > perm;
vector<pair<int, vector<int> > > op;

void scales_init() {
    vector<int> gen = {1, 2, 3, 4, 5, 6};
    do perm.emplace_back(gen);
    while(next_permutation(gen.begin(), gen.end()));

    for(int b = 0; b < 1 << 6; b++) if(__builtin_popcount(b) == 3) {
        vector<int> now;
        for(int i = 0; i < 6; i++) if(b >> i & 1)
            now.emplace_back(i);
        for(int i = 1; i <= 3; i++) op.emplace_back(i, now);
        for(int i = 0; i < 6; i++) if(!(b >> i & 1)) {
            vector<int> tmp = now;
            tmp.emplace_back(i);
            op.emplace_back(4, tmp);
        }
    } 
}

void init(int T) {
    scales_init();
}

void solve(vector<int> vec, int p) {
    if(vec.size() == 1) {
        int *ans = new int[6];
        for(int i = 0; i < 6; i++) ans[perm[vec[0]][i]-1] = i + 1;
        answer(ans);
        return;
    }
    int T = op[tree[p]].x, retQuery;
    vector<int> ask = op[tree[p]].y;
    vector<int> ans[6];

    if(T == 1) retQuery = getHeaviest(ask[0] + 1, ask[1] + 1, ask[2] + 1);
    if(T == 2) retQuery = getLightest(ask[0] + 1, ask[1] + 1, ask[2] + 1);
    if(T == 3) retQuery = getMedian(ask[0] + 1, ask[1] + 1, ask[2] + 1);
    if(T == 4) retQuery = getNextLightest(ask[0] + 1, ask[1] + 1, ask[2] + 1, ask[3] + 1);

    for(int idx : vec) {
        vector<pii> now;
        for(int i = 0; i < 3; i++) now.emplace_back(perm[idx][ask[i]], ask[i]);
        sort(now.begin(), now.end());
        
        if(T == 1) ans[now[2].y].emplace_back(idx);
        if(T == 2) ans[now[0].y].emplace_back(idx);
        if(T == 3) ans[now[1].y].emplace_back(idx);
        if(T == 4) {
            bool valid = false;
            for(int i = 0; i < 3; i++) if(now[i].x > perm[idx][ask[3]]) {
                ans[now[i].y].emplace_back(idx);
                valid = true;
                break;
            }
            if(!valid) ans[now[0].y].emplace_back(idx);
        }
    }
    int step = 0;
    for(int i = 0; i < 6; i++) if(ans[i].size()) {
        ++step;
        if(i == retQuery - 1) solve(ans[i], p * 3 + step);
    }
}

void orderCoins() {
    vector<int> vec(720);
    iota(vec.begin(), vec.end(), 0);
    solve(vec, 0);
}