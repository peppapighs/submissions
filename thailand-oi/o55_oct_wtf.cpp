#include <bits/stdc++.h>

using namespace std;

int n;
int Y[6] = { 5, 7, 19, 76, 86, 87 };
int N[4] = { 3, 31, 33, 78 };

int main() {
	scanf("%d", &n);
	for(int i = 0; i < 6; i++) if(Y[i] == n) return !printf("yes");
	for(int i = 0; i < 4; i++) if(N[i] == n) return !printf("no");

	return 0;
}
