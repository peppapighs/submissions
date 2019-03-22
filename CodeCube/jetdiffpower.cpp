#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int n, A;
int S[N];
long long ret;

long long sq(int a) { return 1LL*a*a; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &S[i]);
	scanf("%d", &A);
	if(n == 1) return !printf("%d\n", A*S[1]);
	if(S[1] < S[2]) {
		if(A/2 < S[2]-S[1]) S[1] += A/2, ret += sq(A/2);
		else S[1] += S[2]-S[1], ret += sq(S[2]-S[1]);
	}
	if(S[n-1] < S[n]) {
		if(A/2 < S[n]-S[n-1]) S[n-1] += A/2, ret += sq(A/2);
		else S[n-1] += S[n]-S[n-1], ret += sq(S[n]-S[n-1]);
	} 
	for(int i = 2; i <= n-1; i++) if(S[i-1] > S[i] && S[i] < S[i+1]) {
		int mn = min(S[i-1], S[i+1]);
		if(A < mn-S[i]) S[i] += A, ret += sq(A);
		else S[i] += mn-S[i], ret += sq(mn-S[i]);		
	}
	for(int i = 1; i < n; i++) ret += 1LL*A*(abs(S[i]-S[i+1]));
	printf("%lld\n", ret);

	return 0;
}