#include "meetings.h"
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e3+5;
 
mt19937 rng(time(NULL));
 
void connect(int a, int b) {
    if(a > b) swap(a, b);
    Bridge(a, b);
}
 
vector<int> sub[N];
 
void solve(vector<int> vec) {
    if(vec.size() < 2) return;
    for(int x : vec) sub[x].clear();
    shuffle(vec.begin(), vec.end(), rng);
 
    int a = vec[0], b = vec[1];
    vector<int> path;
    for(int i = 2; i < vec.size(); i++) {
        int now = Query(a, b, vec[i]);
        sub[now].emplace_back(vec[i]);
        if(now == vec[i]) path.emplace_back(now);
    }
    sub[a].emplace_back(a), sub[b].emplace_back(b);
    sort(path.begin(), path.end(), [&](int x, int y) {
        return Query(x, y, b) == y;
    });
    path.insert(path.begin(), a), path.emplace_back(b);
    for(int i = 0; i < path.size() - 1; i++)
        connect(path[i], path[i + 1]);
 
    for(int x : path) solve(sub[x]);
}
 
void Solve(int n) {
    vector<int> vec;
    for(int i = 0; i < n; i++) vec.emplace_back(i);
    solve(vec);
}
