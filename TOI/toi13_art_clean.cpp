#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int tree[N];

void update(int x, int k) { for(int i = x; i; i -= i & (-i)) tree[i] += k; }
int query(int x) { int sum = 0; for(int i = x; i < N; i += i & (-i)) sum += tree[i]; return sum; }

struct node {
	int x, h, o;
	node(int x, int h, int o) : x(x), h(h), o(o) {}
	friend bool operator<(const node &a, const node &b) {
		return a.x < b.x;
	}
};

int n, t, ans;
vector<node> que;

int main() {
	scanf("%d%d", &n, &t);
	while(n--) {
		int s, h, w, o;
		scanf("%d%d%d%d", &s, &h, &w, &o);
		que.emplace_back(s, h, o);
		que.emplace_back(s + w, h, -o);
	}
	sort(que.begin(), que.end());
	int px = que[0].x;
	int col = 0;
	for(node q : que) {
		ans += (col * (q.x - px));
		update(q.h, q.o);
		int low = 1, high = 0;
		int l = 1, r = N - 1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(query(mid) <= t) r = mid - 1, low = mid;
			else l = mid + 1;
		}
		l = 1, r = N - 1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(query(mid) >= t) l = mid + 1, high = mid;
			else r = mid - 1;
		}
		col = high - low + 1, px = q.x;
	}

	printf("%d", ans);

	return 0;
}