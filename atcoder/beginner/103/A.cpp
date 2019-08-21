#include <bits/stdc++.h>

using namespace std;

int arr[5];

int main() {
	for(int i = 0; i < 3; i++) scanf("%d", &arr[i]);
	sort(arr, arr + 3);
	printf("%d", arr[2] - arr[0]);

	return 0;
}
