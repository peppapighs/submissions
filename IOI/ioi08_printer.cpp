#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 5e5+5;
 
int n, ptr;
int t[N][30], sub[N];
bitset<N> leaf;
vector<char> C;
 
int subLen(int u) {
	sub[u] = 0;
	for(int i = 0; i < 26; i++) {
		int v = t[u][i];
		if(v == -1) continue;
		subLen(v);
		sub[u] = max(sub[v]+1, sub[u]);
	}
}
 
void dfs(int u) {
	if(leaf[u]) C.emplace_back('P');
	int mx = 0, hv = -1;
	for(int i = 0; i < 26; i++) {
		int v = t[u][i];
		if(v == -1) continue;
		if(sub[v] > mx) mx = sub[v], hv = i;
	}
	for(int i = 0; i < 26; i++) {
		int v = t[u][i];
		if(v == -1 || i == hv) continue;
		C.emplace_back('a'+i);
		dfs(v);
	}
	if(hv != -1) {
		C.emplace_back('a'+hv);
		dfs(t[u][hv]);
	} 
	C.emplace_back('-');
}
 
int main() {
	memset(t, -1, sizeof t);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char A[25];
		scanf(" %s", A+1);
		int cptr = 0;
		for(int i = 1; i <= strlen(A+1); i++) {
			int &pos = t[cptr][A[i]-'a'];
			if(pos == -1) pos = ++ptr;
			cptr = pos;
		}
		leaf[cptr] = 1;
	}
	subLen(0);
	dfs(0);
	while(!C.empty() && C.back() == '-') C.pop_back();
	printf("%d\n", C.size());
	for(char c : C) printf("%c\n", c);
 
	return 0;
}