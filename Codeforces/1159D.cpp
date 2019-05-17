#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, k;

int main() {
    scanf("%d %d", &n, &k);
    int diff = (n - k) >> 1;
    int md = diff + 1;
    for(int i = 0; i < n; i++) {
        if(i % md == diff) printf("1");
        else printf("0");
    }
    printf("\n");

    return 0;
}