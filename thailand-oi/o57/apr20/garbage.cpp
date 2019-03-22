#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

const int N = 1e4+5;
const int M = 1e5+5;

int n, m, q, par[N];
int l[M], r[M];
int A[M], B[M];
vector<iii> E;

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1, a, b, c; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		E.emplace_back(c, a, b);
	}
	sort(E.begin(), E.end());
	scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		scanf("%d %d", A+i, B+i);
		l[i] = 0, r[i] = m-1;
	}
	vector<vector<int> > pos(m);
	for(int step = 1; step <= m; step <<= 1) {
		iota(par, par+N, 0);
		for(int i = 1; i <= q; i++) if(l[i] < r[i]) pos[(l[i] + r[i]) >> 1].emplace_back(i);
		for(int i = 0; i < E.size(); i++) {
			int a = get<1>(E[i]), b = get<2>(E[i]);
			if(find(a) != find(b)) par[find(a)] = find(b);
			while(!pos[i].empty()) {
				int idx = pos[i].back(); pos[i].pop_back();
				if(find(A[idx]) == find(B[idx])) r[idx] = i;
				else l[idx] = i + 1;
			}
		}	
	}
	for(int i = 1; i <= q; i++) printf("%d\n", get<0>(E[r[i]]));

	return 0;
}