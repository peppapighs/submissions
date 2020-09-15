#include "interactive.h"
#include <bits/stdc++.h>
 
#define pii pair<int, int>
#define x first
#define y second
 
using namespace std;
 
const int N = 105;
 
vector<int> get_xor(vector<int> vec) {
	if(vec.empty()) return vector<int>();
 
	map<int, int> mp;
	vector<int> ret = get_pairwise_xor(vec), ans;
 
	for(int x : ret) if(x != 0) {
		if(mp[x] == 1) ans.emplace_back(x), mp[x] ^= 1;	
		else mp[x] = 1;
	}	
	assert(ans.size() == vec.size() * (vec.size() - 1) / 2);
	return ans;
}
 
int A[N];
map<int, int> pos;
 
vector<int> guess(int n) {
	A[1] = ask(1);
	
	for(int bit = 0; bit < 7; bit++) {
		vector<int> ask;	
		for(int i = 2; i <= n; i++) if(i >> bit & 1)
			ask.emplace_back(i);
 
		vector<int> wo_one = get_xor(ask);
		ask.emplace_back(1);
		vector<int> w_one = get_xor(ask);
 
		for(int x : wo_one) 
			w_one.erase(find(w_one.begin(), w_one.end(), x));
		for(int x : w_one) pos[x ^ A[1]] += (1 << bit);
	}
	for(pii p : pos) A[p.y] = p.x;
	
	return vector<int>(A + 1, A + n + 1);
}