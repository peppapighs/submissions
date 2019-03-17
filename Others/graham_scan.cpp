#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int n;
pii low;
vector<pii> V, hull;

int bad(pii a, pii b, pii c) {
	pii vec1(b.x - a.x, b.y - a.y), vec2(c.x - a.x, c.y - a.y);
	if(vec1.x * vec2.y - vec1.y * vec2.x < 0) return 1;
	else if(vec1.x * vec2.y - vec1.y * vec2.x == 0) return 0;
	return 2;
}

double d(pii a, pii b) {
	long p2 = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); 
	return sqrt(p2);
}

double solve() {
	if(V.size() == 1) return 0;
	if(V.size() == 2) return 2.0 * d(V[0], V[1]);
	hull.clear();
	sort(V.begin(), V.end(), [&](const pii &a, const pii &b) {
		if(a.y != b.y) return a.y > b.y;
		return a.x > b.x;
	});
	low = V.back(), V.pop_back();
	sort(V.begin(), V.end(), [&](const pii &a, const pii &b) {
		int o = bad(low, a, b);
		if(o == 0) return d(low, a) < d(low, b);
		return o == 2;
	});
	hull.emplace_back(low), hull.emplace_back(V[0]);
	for(int i = 1; i < (int)V.size(); i++) {
		while(hull.size() > 2 && bad(hull[hull.size()-2], hull[hull.size()-1], V[i]) != 2) hull.pop_back();
		hull.emplace_back(V[i]);
	}
	double ret = 0;
	for(int i = 0; i < (int)hull.size(); i++) ret += d(hull[i], hull[(i + 1) % hull.size()]);
	V.emplace_back(low);
	return ret;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1, a, b; i <= n; i++) {
		scanf("%d %d", &a, &b);
		V.emplace_back(a, b);
		printf("%f\n", solve());
	}

	return 0;
}