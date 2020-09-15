#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1 << 19;
 
int n, k, t, s;
mt19937 rng(time(NULL));
 
void print(int val) {
	vector<int> vec;
	for(int i = 0; i < n; i++, val >>= 1)
		vec.emplace_back(val & 1);
	reverse(vec.begin(), vec.end());
	for(int x : vec) printf("%d", x);
	printf("\n");
}
 
int chk[N], ans[N];
vector<int> base;
 
bool is_basis() {
	vector<int> mat(base.begin(), base.begin() + n);
	for(int i = n - 1; ~i; i--) {
		int val = -1;
		for(int x : mat) if(x >> i & 1) val = x;
		if(val == -1) return false;
		for(int &x : mat) if(x != val && (x >> i & 1))
			x ^= val;	
	}
	return true;
}
 
int main() {
	char input[100];
	scanf("%d %d %d %s", &n, &k, &t, input);
	if(k % 2 == 0) return !printf("-1\n");
 
	for(int i = 0; input[i] != '\0'; i++)
		s = (s << 1) + (input[i] == '1');
 
	for(int i = 0; i < (1 << n); i++) if(__builtin_popcount(i) == k)
		base.emplace_back(i);
 
	while(true) {
		shuffle(base.begin(), base.end(), rng);
		if(!is_basis()) continue;
 
		ans[0] = s;
		int ptr = 1, valid = 1;
		for(int j = 0; j < n; j++) for(int i = ptr - 1; ~i; i--) {
			ans[ptr] = ans[i] ^ base[j];
			if(!chk[ans[ptr]]) chk[ans[ptr]] = 1;
			else {
				valid = 0;
				break;
			}
			++ptr;
		}
 
		if(valid) {
			printf("%d\n", (1 << n));
			for(int i = 0; i < (1 << n); i++) print(ans[i]);
			exit(0);
		} else for(int i = 0; i < (1 << n); i++) chk[ans[i]] = 0;
	}
 
	return 0;
}