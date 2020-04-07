#include <bits/stdc++.h>

using namespace std;

const int N = 105;

char A[N];

void solve(int idx) {
    scanf(" %s", A + 1);
    printf("Case #%d: ", idx);
    int dep = 0;
    for(int i = 1; A[i] != '\0'; i++) {
        int now = A[i] - '0';
        while(dep < now) printf("("), ++dep;
        while(dep > now) printf(")"), --dep;
        printf("%d", now);
    }
    while(dep > 0) printf(")"), --dep;
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}