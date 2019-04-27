#include "messy.h"
#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> ans;

string gen_base(int l, int r, int idx) {
    string s(n, '1');
    for(int i = l; i <= r; i++) s[i] = '0';
    s[idx] = '1';
    return s;
}

string gen_find(vector<int> &v, int idx) {
    string s(n, '1');
    for(int pos : v) s[pos] = '0';
    s[idx] = '1';
    return s;
}

void build(int l = 0, int r = n-1) {
    if(l == r) return;
    int mid = (l + r) >> 1;
    for(int i = l; i <= mid; i++) add_element(gen_base(l, r, i));
    build(l, mid), build(mid+1, r);
}

void restore(vector<int> &v, int l = 0, int r = n-1) {
    if(l == r) return void(ans[v[0]] = l);
    vector<int> L, R;
    for(int pos : v) {
        if(check_element(gen_find(v, pos))) L.emplace_back(pos);
        else R.emplace_back(pos);
    }
    int mid = (l + r) >> 1;
    restore(L, l, mid), restore(R, mid+1, r);
}

vector<int> restore_permutation(int _n, int w, int r) {
    n = _n; 
    build(), compile_set();

    vector<int> v;
    for(int i = 0; i < n; i++) v.emplace_back(i);
    ans = vector<int>(n, 0);
    restore(v);

    return ans;
}