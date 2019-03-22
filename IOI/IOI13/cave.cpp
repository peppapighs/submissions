#include "cave.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 5e3+5; 

int n;
int S[N], D[N];
bool chk[N];

void exploreCave(int N) {
	n = N;
	for(int i = 0; i < n; i++) {
		int init = tryCombination(S);
		bool t = (init == -1 || init > i);
		int l = 0, r = n-1;
		while(l < r) {
			int m = (l + r) >> 1;
			for(int j = l; j <= m; j++) if(!chk[j]) S[j] ^= 1;
			int ret = tryCombination(S);
			bool now = (ret == -1 || ret > i);
			if(t ^ now) r = m, t = now;
			else l = m+1;
		}
		if(!t) S[r] ^= 1;
		D[r] = i, chk[r] = true;
	}
	answer(S, D);
}
