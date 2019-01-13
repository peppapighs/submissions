#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

int arr[N], bill[N];
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
	for(int i = 0; i < m; i++) scanf("%d", &bill[i]);
	int i = 0, j = 0, ans = 0;
	while(i < n && j < m) {
		if(bill[j] >= arr[i]) ans++, j++, i++;
		else i++;
	}

	printf("%d", ans);

	return 0;
}