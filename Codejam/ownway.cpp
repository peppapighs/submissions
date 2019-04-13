#include <bits/stdc++.h>

using namespace std;

int n;
char A[100005];

void solve(int idx) {
    scanf("%d %s", &n, A+1); 
    printf("Case #%d: ", idx);
    for(int i = 1; i <= 2*n-2; i++) {
        if(A[i] == 'S') printf("E");
        else printf("S");
    }
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}
