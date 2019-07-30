#include "group.h"
#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n;
vector<pii> v;

int getMinimumDelay(int N, vector<int> X, vector<int> Y) {
    n = N; 
    long mnx = 2e9, mny = 2e9, mxx = -2e9, mxy = -2e9;
    for(int i = 0; i < n; i++) {
        v.emplace_back(X[i] + Y[i], X[i] - Y[i]);
        mnx = min(mnx, v.back().x), mny = min(mny, v.back().y);
        mxx = max(mxx, v.back().x), mxy = max(mxy, v.back().y);
    }
    long l = 0, r = 2e9;
    while(l < r) {
        long mid = (l + r) >> 1;
        bool valid_l = true, valid_r = true;
        for(int i = 0; i < n; i++) {
            valid_l &= (v[i].x <= mnx + mid && v[i].y <= mny + mid) || (mxx - mid <= v[i].x && mxy - mid <= v[i].y);
            valid_r &= (v[i].x <= mnx + mid && v[i].y >= mxy - mid) || (mxx - mid <= v[i].x && mny + mid >= v[i].y);
        }
        if(valid_l || valid_r) r = mid;
        else l = mid + 1;
    }
    return (int)r;
}

