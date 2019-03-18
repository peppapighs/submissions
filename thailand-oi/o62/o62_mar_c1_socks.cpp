#include "sockslib.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 2e3+5;

int n;
bool chk[N];

bool f(int l, int r) {
    int cnt = 0;
    vector<int> vec;
    for(int i = l; i <= r; i++) if(!chk[i]) {
        vec.emplace_back(i);
        ++cnt;
    }
    return ask(vec) < cnt;
}

int main() {
    n = 2 * num();
    for(int i = n; i; i--) if(!chk[i]) {
        int l = i, r = n;
        bool valid = false;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(f(i, mid)) r = mid, valid = true;
            else l = mid + 1;
        }
        if(!valid && !f(i, r)) continue;
        match(i, r);
        chk[i] = chk[r] = true;
    }

    return 0;
}