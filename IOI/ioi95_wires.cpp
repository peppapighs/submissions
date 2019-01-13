#include "wirelib.h"
#include <bits/stdc++.h>

using namespace std;

int n;
int S[95];
bool C[95];

void solve(int l, int r, vector<int>& V) {
        if(l == r) {
                for(int v : V) S[v] = l;
                return;
        }
        int m = (l + r) >> 1;
        for(int i = l; i <= m; i++) if(!C[i]) C[i] = cmd_C(i);
        for(int i = m+1; i <= r; i++) if(C[i]) C[i] = cmd_C(i);
        vector<int> L, R;
        for(int v : V) {
                if(cmd_T(v)) L.emplace_back(v);
                else R.emplace_back(v);
        }
        solve(l, m, L), solve(m+1, r, R);
}

int main() {
	n = wire_init();
        vector<int> V;
        for(int i = 1; i <= n; i++) V.emplace_back(i);
        solve(1, n, V);
        cmd_D(S);

	return 0;
}
