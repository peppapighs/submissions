#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

char f(char a, int x) {
	if(a == 'a') return 'b';
	else if(a == 'z') return 'y';
	else return a + x;
}

int pos[2] = {1, -1};

int main() {
	int T;
	cin >> T;
	while(T--) {
		int n;
		scanf("%d", &n);
		string s;
		cin >> s;
		bool val = true;
		for(int i = 0; i < n/2; i++) {
			bool valid = false;
			for(int x = 0; x < 2; x++) {
				for(int y = 0; y < 2; y++) {
					if(f(s[i], pos[x]) == f(s[n-i-1], pos[y])) valid = true;
				}
			}
			if(!valid) {
				printf("NO\n"), val = false;
				break;
			}
		}
		if(val) printf("YES\n");
	}

	return 0;
}