#include "towns.h"
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 205;

int hubDistance(int n, int sub) {
    int u = 0, v = 0;
    vector<vector<int> > d(n, vector<int>(n));
    vector<int> branch(n);

    auto get = [&](int a, int b) {
        if(a == b) return 0;
        if(d[a][b]) return d[a][b];
        return d[a][b] = d[b][a] = getDistance(a, b);
    };

    //Find 2 farthest nodes
    for(int i = 0; i < n; i++) if(i != 0 && get(0, i) > get(0, u)) u = i;
    for(int i = 0; i < n; i++) if(i != u && get(u, i) > get(u, v)) v = i;
 
    //Get hub candidates on 0-u path
    int lim = (get(0, u) + get(u, v) - get(0, v)) / 2;
    vector<int> hub;
    for(int i = 0; i < n; i++) {
        branch[i] = (get(u, i) + get(0, u) - get(0, i)) / 2;
        if(branch[i] <= lim) hub.emplace_back(branch[i]);
    }    
    sort(hub.begin(), hub.end());
    hub.resize(unique(hub.begin(), hub.end()) - hub.begin());
 
    //Find hubs
    int ans = get(u, v), rot = -1, rot2 = -1;
    for(int pos : hub) {
        int r = max(pos, get(u, v) - pos);
        if(r <= ans) {
            if(r == ans) swap(pos, rot), swap(pos, rot2);
            else rot = pos, rot2 = -1;
            ans = r;
        }
    }

    //Boyer-Moore Majority Vote Algorithm
    auto boyer_moore = [&](int p) {
        auto same = [&](int a, int b) {
            int ba = branch[a], bb = branch[b];
            if(ba == p && bb == p)
                return get(a, b) < get(0, a) + get(u, b) - get(0, u);
            else return (ba < p && bb < p) || (ba > p && bb > p);
        };
    
        int last = -1, total = 0;
        vector<int> col(n);
        for(int i = 0, cnt = 0; i < n; i++) {
            if(!cnt) last = i, ++cnt, col[i] = 0;
            else if(same(i, last)) ++cnt, col[i] = 1;
            else --cnt, col[i] = 2;
        }
        bool valid = false;
        for(int i = 0, cnt = 0; i < n; i++) {
            if(!col[i]) {
                ++cnt;
                if(same(i, last)) ++total, valid = true;
            } else if(col[i] == 1) ++cnt, total += valid;
            else {
                total += same(i, last);
                if(!--cnt) valid = false;
            }
        }
        if(total > n / 2) return false;
        else return true;
    };

    if(boyer_moore(rot) || (rot2 != -1 && boyer_moore(rot2))) return ans;
    else return -ans;
}