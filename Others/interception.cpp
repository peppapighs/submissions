#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	cin >> t;
	for(int q = 1;q <= t;q++) {
		int n;
		cin >> n;
		for(int i = 0;i <= n;i++) {
			int a;
			cin >> a;
		}
		printf("Case #%d: ", q);
		if(n & 1) printf("1\n0.0\n");
		else printf("0\n");
	}

	return 0;
}