#include <bits/stdc++.h>

using namespace std;

const int M = 29947;

int a, b, c;
int dp[355][355][355];

void sort(int &x, int &y, int &z) {
	if(x < y) swap(x, y);
	if(x < z) swap(x, z);
	if(y < z) swap(y, z);
}

int solve(int x, int y, int z) {
	sort(x, y, z);
	int &ret = dp[x][y][z];
	if(~ret) return ret;
	if(!x && !y && !z) return ret = 1;
	ret = solve(x-1, y, z);
	for(int i = 1; i <= y; i++) {
		ret += solve(x-1, y-i, z);
		ret %= M;
	}
	for(int i = 1; i <= z; i++) {
		ret += solve(x-1, z-i, 0) * solve(y, i-1, 0);
		ret %= M;
	}
	return ret;
}

int main() {
	memset(dp, -1, sizeof dp);
	scanf("%d %d %d", &a, &b, &c);
	printf("%d\n", solve(a-1, b-1, c-1));
	
	return 0;
}