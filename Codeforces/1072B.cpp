#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define x first
#define y second

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

//-----------------------------------------------------------

const int N = 1e5+5;

int n;
int A[N], B[N];
bool dp[N][4];

int main() {
       scanf("%d", &n);
       for(int i = 1; i < n; i++) scanf("%d", A+i);
       for(int i = 1; i < n; i++) scanf("%d", B+i);
       for(int i = 0; i <= 3; i++) dp[1][i] = 1;
       for(int i = 2; i <= n; i++) 
              for(int j = 0; j <= 3; j++) 
                     for(int k = 0; k <= 3; k++) 
                            if((j | k) == A[i-1] && (j & k) == B[i-1])
                                   dp[i][j] |= dp[i-1][k];
       for(int i = 0; i <= 3; i++) if(dp[n][i]) {
              vector<int> V;
              int p = i;
              V.emplace_back(i);
              for(int j = n-1; j; j--) {
                     for(int k = 0; k <= 3; k++) if((V.back() | k) == A[j] && (V.back() & k) == B[j] && dp[j][k]) {
                            V.emplace_back(k);
                            break;
                     }
              }
              reverse(V.begin(), V.end());
              printf("YES\n");
              for(int v : V) printf("%d ", v);
              printf("\n");
              return 0;
       }
       printf("NO\n");

	return 0;
}