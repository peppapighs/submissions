#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n;
pii A[N];

int main() {
       while(scanf("%d", &n), n != 0) {
              for(int i = 1; i <= n; i++) scanf("%d %d", &A[i].x, &A[i].y);
              sort(A+1, A+n+1);
              vector<int> LIS;
              for(int i = 1; i <= n; i++) {
                     if(LIS.empty() || A[i].y >= LIS.back()) LIS.emplace_back(A[i].y);
                     else {
                            auto it = upper_bound(LIS.begin(), LIS.end(), A[i].y);
                            if(it == LIS.end()) continue;
                            *it = A[i].y;
                     }
              }
              printf("%d\n", LIS.size());
       }

       return 0;
}