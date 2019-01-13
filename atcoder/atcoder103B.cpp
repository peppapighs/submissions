#include <bits/stdc++.h>

using namespace std;

int main() {
	string a, b;
	cin >> a >> b;
	for(int i = 0; i < a.length(); i++) {
		char t = b[b.length() - 1];
		b = b.substr(0, b.length() - 1);
		b = t + b;
		bool test = true;
		for(int i = 0; i < a.length(); i++) test &= (a[i] == b[i]);
		if(test) return !printf("Yes");
	}
	printf("No");

	return 0;
}
