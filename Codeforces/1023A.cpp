#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

//-----------------------------------------------------------

int main() {
	int n, m;
	cin >> n >> m;
	string s, t;
	cin >> s >> t;
	int at = -1;
	for(int i = 0; i < n; i++) if(s[i] == '*') at = i;
	if(at == -1 && s != t) return !printf("NO");
	else if(at == -1 && s == t) return !printf("YES");
	string a = s.substr(0, at), b = s.substr(at+1, n-at);
	if(a.length() + b.length() > t.length()) return !printf("NO");
	if(a == t.substr(0, a.length()) && b == t.substr(m-b.length() , b.length())) printf("YES");
	else printf("NO");

	return 0;
}