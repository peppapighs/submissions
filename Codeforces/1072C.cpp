#include <bits/stdc++.h>

using namespace std;

#define long long long
#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

//-----------------------------------------------------------

long a, b, n;
vector<int> N, M;

int main() {
       scanf("%lld %lld", &a, &b);
       while((n+1) * (n+2) / 2LL <= a+b) n++;
       for(int i = n; i; i--) {
              if(i <= a) N.emplace_back(i), a -= i;
              else if(i <= b) M.emplace_back(i), b -= i;
       }
       printf("%d\n", N.size());
       for(int i : N) printf("%d ", i);
       printf("\n");
       printf("%d\n", M.size());
       for(int i : M) printf("%d ", i);
       printf("\n");

	return 0;
}
