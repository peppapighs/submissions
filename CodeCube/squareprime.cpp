#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

long long sieve[N],a,b;
vector<int> prime;
vector<long long> sqp;

int main() {
	for(int i=2;i<N;i++) {
		if(!sieve[i]) {
			prime.emplace_back(i);
			for(int j=i+i;j<N;j+=i) {
				sieve[j]=1;;
			}
		}
	}
	for(long long p : prime) {
		sqp.emplace_back(p*p);
	}
	scanf("%lld%lld",&a,&b);
	int cnt=0;
	for(long long p : sqp) {
		if(a<=p&&p<=b) {
			printf("%lld ",p);
			cnt++;
		}
	}
	
	if(!cnt) printf("-1");

	return 0;
}