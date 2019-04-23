#include "doll.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;
const int INF = 1e9+1;

int n, m, ptr;
vector<int> C, X, Y;

int solve(vector<int> &V) {
    if((int)V.size() == 1 || (V[0] == -INF && V.back() == -INF)) return V[0];
    vector<int> L, R;
    for(int i = 0; i < (int)V.size(); i++) {
        if(i & 1) R.emplace_back(V[i]);
        else L.emplace_back(V[i]);
    }
    int l = solve(L), r = solve(R);
    X.emplace_back(l), Y.emplace_back(r);
    return --ptr;
}

void create_circuit(int M, vector<int> A) {
    A.emplace_back(0);
    n = A.size(), m = M;
    
    int L = 0, sz;
    while((1 << L) < (int)A.size()) ++L;
    sz = 1 << L;

    vector<int> V;
    for(int i = 0; i < sz; i++) {
        int pos = 0;
        for(int j = 0; j < L; j++) pos += (i >> j & 1) << (L - j - 1);
        V.emplace_back(pos >= sz - n); 
    }
    for(int i = 0, idx = 0; i < sz; i++) {
        if(V[i]) V[i] = A[idx++];
        else V[i] = -INF;
    }

    int root = solve(V);

    C = vector<int>(m+1, root);
    for(int &v : X) if(v == -INF) v = root;
    for(int &v : Y) if(v == -INF) v = root;

    answer(C, X, Y);
}