#include "elephants.h"
#include <bits/stdc++.h>
 
#define pii pair<int, int>
#define x first
#define y second
 
using namespace std;
 
const int N = 1.5e5 + 5;
const int B = 390;
 
int n, k, bcnt;
int R[B + 5], pos[N];
map<int, int> mp;
vector<int> jump[B + 5], cnt[B + 5], bucket[B + 5];
 
void init(int _n, int _k, int X[]) {
    n = _n, k = _k;
    for(int i = 0; i < n; i++) ++mp[pos[i] = X[i]];
}
 
void solve_bucket(int idx) {
    vector<int> &vec = bucket[idx];
 
    jump[idx] = vector<int>(vec.size()), cnt[idx] = vector<int>(vec.size());
    for(int i = vec.size() - 1, j = vec.size(); ~i; i--) {
        while(vec[j - 1] > vec[i] + k) --j;
        if(j < vec.size()) jump[idx][i] = jump[idx][j], cnt[idx][i] = cnt[idx][j] + 1;
        else jump[idx][i] = vec[i] + k, cnt[idx][i] = 1;
    }
}
 
void revalidate() {
    bcnt = 0;
    for(pii p : mp) {
        if(!bcnt || bucket[bcnt - 1].size() >= B)
            bucket[bcnt++].clear();
        bucket[bcnt - 1].emplace_back(p.x);
    }
    for(int i = 0; i < bcnt; i++) {
        if(i + 1 < bcnt) R[i] = bucket[i + 1][0] - 1;
        else R[i] = 2e9;
 
        solve_bucket(i);
    } 
}
 
void add_elephant(int x, bool b) {
    int ptr = -1;
    while(R[++ptr] < x);
    int idx = lower_bound(bucket[ptr].begin(), bucket[ptr].end(), x) - bucket[ptr].begin();
 
    if(b) bucket[ptr].insert(bucket[ptr].begin() + idx, x);
    else bucket[ptr].erase(bucket[ptr].begin() + idx);
 
    solve_bucket(ptr);
}
 
int counter;
 
int update(int i, int y) {
    if(counter++ % B == 0) revalidate();
 
    if(!--mp[pos[i]]) add_elephant(pos[i], 0), mp.erase(pos[i]);
    if(!mp[y]) add_elephant(y, 1);
    ++mp[y], pos[i] = y;
 
    int answer = 0, cur = -1;
    for(int i = 0; i < bcnt; i++) {
        int idx = upper_bound(bucket[i].begin(), bucket[i].end(), cur) - bucket[i].begin();
        if(idx < bucket[i].size())
            answer += cnt[i][idx], cur = jump[i][idx];
    }
 
    return answer;
}