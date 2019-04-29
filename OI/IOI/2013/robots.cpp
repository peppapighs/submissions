#include "robots.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

vector<pii> toy;

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    for(int i = 0; i < T; i++) toy.emplace_back(W[i], S[i]);
    sort(toy.begin(), toy.end());
    sort(X, X+A), sort(Y, Y+B);

    auto chk = [&](int mid) {
        priority_queue<pii> Q;
        vector<bool> sel(T);
        int j = 0;
        for(int i = 0; i < A; i++) {
            int cnt = 0;
            while(j < T && toy[j].x < X[i]) Q.emplace(toy[j].y, j), ++j;
            while(!Q.empty() && cnt < mid) sel[Q.top().y] = true, Q.pop(), ++cnt;
        }
        while(j < T) Q.emplace(toy[j].y, j), ++j;
        for(int i = B-1; ~i; i--) {
            int cnt = 0;
            while(!Q.empty() && cnt < mid) {
                pii now = Q.top(); Q.pop();
                if(now.x >= Y[i]) continue;
                sel[now.y] = true, ++cnt;
            }
        }
        for(int i = 0; i < T; i++) if(!sel[i]) return false;
        return true;
    };

    int l = 0, r = T;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(chk(mid)) r = mid;
        else l = mid+1;
    }
    if(!chk(r)) return -1;
    else return r;
}