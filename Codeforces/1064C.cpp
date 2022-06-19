#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
char S[N];

int main() {
    scanf("%d", &n);
    scanf(" %s", S + 1);
    sort(S + 1, S + n + 1);
    printf("%s\n", S + 1);

    return 0;
}
