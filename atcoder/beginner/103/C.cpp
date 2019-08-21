#include <bits/stdc++.h>

using namespace std;

int n;
long long ans;

int main() {
	scanf("%d", &n);
	while(n--) {
		long long t;
		scanf("%lld", &t);
		ans += (t - 1);
	}
	printf("%lld", ans);

	return 0;
}
