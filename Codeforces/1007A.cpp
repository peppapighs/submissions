#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

const int N = 1e5 + 5;

int A[N];
vector<int> arr;
int n, ans;

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
		arr.emplace_back(A[i]);
	}

	sort(arr.begin(), arr.end());
	int idx = -1, a = arr[0];
	for(int i = 1; i < n; i++) if(arr[i] > a) {
		idx = i;
		break;
	}
	if(idx == -1) return !printf("0");
	int i = 0, j = idx;
	while(i < n && j < n) {
		if(arr[i] < arr[j]) {ans++; i++; j++;}
		else j++;
	}

	printf("%d", ans);

	return 0;
}