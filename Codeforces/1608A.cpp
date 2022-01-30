#include <bits/stdc++.h>

using namespace std;

int n;

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) printf("%d ", i + 1);
    printf("\n"); 
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}