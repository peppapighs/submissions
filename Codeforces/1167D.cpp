#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, dep[N];
char s[N];
stack<int> S;

int main() {
    scanf("%d %s", &n, s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') {
            dep[i] = S.size() + 1;
            S.emplace(i);
        } else {
            dep[i] = dep[S.top()];
            S.pop();
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d", dep[i] & 1);
    printf("\n");

    return 0;
}