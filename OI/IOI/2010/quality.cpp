#include "quality.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 3e3+5;

int cnt[N][N];
pii pos[N*N];

int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	int l = 1, r = R*C;
	for(int i = 0; i < R; i++) for(int j = 0; j < C; j++)
		pos[Q[i][j]] = pii(i+1, j+1);
	while(l < r) {
		bool valid = false;
		int mid = (l + r) >> 1;
		memset(cnt, 0, sizeof cnt);
		for(int i = mid+1; i <= R*C; i++) {
			pii now = pos[i];
			++cnt[now.x][now.y];
		}
		for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++)
			cnt[i][j] += cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
		for(int i = H; i <= R; i++) for(int j = W; j <= C; j++){
			int sum = cnt[i][j] - cnt[i-H][j] - cnt[i][j-W] + cnt[i-H][j-W];
			if(H*W / 2 >= sum) valid = true;
		}
		if(valid) r = mid;
		else l = mid+1;
	}
	return r;
}