#include "Alicelib.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;


void Alice(int n, int m, int A[], int B[]){
	vector<pii> E;
	for(int i = 0; i < m; i++) E.emplace_back(A[i], B[i]);
	for(int i = 0; i <= 9; i++) {
		for(int j = 0; j < n; j++) if(j >> i & 1)
			E.emplace_back(n + i, j);
		if(i < 9) E.emplace_back(n + i, n + i + 1);
	}
	for(int i = 0; i < n; i++) E.emplace_back(n + 10, i);
	E.emplace_back(n + 10, n + 11);

	InitG(n + 12, (int)E.size());
	for(int i = 0; i < E.size(); i++)
		MakeG(i, E[i].x, E[i].y);
}

