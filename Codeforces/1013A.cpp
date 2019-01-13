#include <bits/stdc++.h>

using namespace std;

int n, sum1, sum2;

int main() {
	scanf("%d", &n);
	for(int i = 1, a; i <= n; i++) scanf("%d", &a), sum1 += a;
	for(int i = 1, a; i <= n; i++) scanf("%d", &a), sum2 += a;

	if(sum1 >= sum2) printf("Yes");
	else printf("No");

	return 0;
}