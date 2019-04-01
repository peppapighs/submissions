#include "sort_weight.h"
#include <bits/stdc++.h>

using namespace std;

bool leq(int a, int b) {
    return sort_weight(a, b) == 1;
}

void ans(int a, int b, int c, int d, int e) {
    vector<int> ret(5);
    ret[a] = 0, ret[b] = 1, ret[c] = 2, ret[d] = 3, ret[e] = 4;
    sort_answer(ret[0], ret[1], ret[2], ret[3], ret[4]);
}

int T;
vector<int> V(5);

int main() {
    T = get_case();
    while(T--) {
        sort_init();
        for(int i = 0; i < 5; i++) V[i] = i;
        if(!leq(V[0], V[1])) swap(V[0], V[1]);
        if(!leq(V[2], V[3])) swap(V[2], V[3]);
        if(!leq(V[1], V[3])) swap(V[1], V[3]), swap(V[0], V[2]);
        if(leq(V[4], V[1])) {
            //V[4] -> _ V[0] _ V[1] V[3]
            if(leq(V[4], V[0])) {
                //V[4] V[0] V[1] V[3]
                if(leq(V[2], V[0])) {
                    if(leq(V[2], V[4])) ans(V[2], V[4], V[0], V[1], V[3]);
                    else ans(V[4], V[2], V[0], V[1], V[3]);
                } else {
                    if(leq(V[2], V[1])) ans(V[4], V[0], V[2], V[1], V[3]);
                    else ans(V[4], V[0], V[1], V[2], V[3]);
                }
            } else {
                //V[0] V[4] V[1] V[3]
                if(leq(V[2], V[4])) {
                    if(leq(V[2], V[0])) ans(V[2], V[0], V[4], V[1], V[3]);
                    else ans(V[0], V[2], V[4], V[1], V[3]);
                } else {
                    if(leq(V[2], V[1])) ans(V[0], V[4], V[2], V[1], V[3]);
                    else ans(V[0], V[4], V[1], V[2], V[3]); 
                }
            }
        } else {
            //V[4] -> V[0] V[1] _ V[3] _
            if(leq(V[4], V[3])) {
                //V[0] V[1] V[4] V[3]
                if(leq(V[2], V[1])) {
                    if(leq(V[2], V[0])) ans(V[2], V[0], V[1], V[4], V[3]);
                    else ans(V[0], V[2], V[1], V[4], V[3]);
                } else {
                    if(leq(V[2], V[4])) ans(V[0], V[1], V[2], V[4], V[3]);
                    else ans(V[0], V[1], V[4], V[2], V[3]);
                }
            } else {
                //V[0] V[1] V[3] V[4]
                if(leq(V[2], V[1])) {
                    if(leq(V[2], V[0])) ans(V[2], V[0], V[1], V[3], V[4]);
                    else ans(V[0], V[2], V[1], V[3], V[4]);
                } else {
                    if(leq(V[2], V[3])) ans(V[0], V[1], V[2], V[3], V[4]);
                    else ans(V[0], V[1], V[3], V[2], V[4]);
                }
            }
        }
    }

    return 0;
}