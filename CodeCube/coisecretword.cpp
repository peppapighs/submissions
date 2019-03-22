#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int T;
pii prm(69, 420);
char A[N], B[N];
pii dp[N];

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%s %s", A, B);
		int n = strlen(A), m = strlen(B);
		pii pw(1, 1), pat(0, 0);
		char ret[N];
		for(int i = 0; i < m ; i++) {
			pat = add(mul(pat, prm), pii(B[i], B[i]));
			pw = mul(pw, prm);
		}
		int ptr = 1;
		dp[0] = pii(0, 0);
		for(int i = 1; i <= n; i++, ptr++) {
			dp[ptr] = add(mul(dp[ptr-1], prm), pii(A[i-1], A[i-1]));
			ret[ptr] = A[i-1];
			if(ptr >= m && sub(dp[ptr], mul(dp[ptr-m], pw)) == pat) ptr -= m;
		}
		ret[ptr] = '\0';
		if(!strlen(ret+1)) printf("No COI Secret Code\n");
		else printf("%s\n", ret+1);
	}

	return 0;
}
