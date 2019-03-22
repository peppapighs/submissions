#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;
const int M = 1e4+7;

int n, q, block, cnt;
int A[N], ans[N];
map<int, int> mp;
vector<pii> D[N];

int modpow(int a, int b) {
	int ret = 1;
	for( ; b; b >>= 1) {
		if(b & 1) ret = (ret * a) % M;
		a = (a * a) % M;
	}
	return ret;
}

void update(int idx, bool del) {
	for(pii d : D[idx]) {
		cnt = (cnt * modpow(mp[d.x]+1, M-2)) % M;
		mp[d.x] += del ? -d.y : d.y;
		cnt = (cnt * (mp[d.x]+1)) % M;
	}
}

int main() {
	scanf("%d %d", &n, &q);
	block = (int)sqrt(n);
	vector<vector<iii> > vec(block + 1);
	for(int i = 0; i < n; i++) {
		scanf("%d", A+i);
		int now = A[i];
		for(int j = 2; j * j <= A[i]; j++) if(now % j == 0) {
			D[i].emplace_back(j, 0);
			while(now % j == 0) now /= j, ++D[i].back().y;
		}
		if(now != 1) D[i].emplace_back(now, 1);
	}
	for(int i = 1, a, b; i <= q; i++) {
		scanf("%d %d", &a, &b);
		--a, --b;
		vec[a / block].emplace_back(a, b, i);
	}
	int L = 0, R = 0;
	for(int i = 0; i <= block; i++) {
		sort(vec[i].begin(), vec[i].end(), [&](const iii &a, const iii &b) {
			return get<1>(a) < get<1>(b);	
		});	
		cnt = 1, L = R = i * block;
		mp.clear();
		for(iii Q : vec[i]) {
			int a, b, idx;
			tie(a, b, idx) = Q;
			while(R <= b) update(R++, 0);
			while(L > a) update(--L, 0);
			while(L < a) update(L++, 1);
			ans[idx] = cnt;
		}
	}
	for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);

	return 0;
}