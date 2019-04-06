#include <bits/stdc++.h>

using namespace std;

int n;
char S[105];
vector<int> A, B;

void solve(int idx) {
    memset(S, 0, sizeof S), A.clear(), B.clear();
    scanf(" %s", S+1);
    n = strlen(S+1);
    for(int i = n; i; i--) {
        if(S[i] == '4') A.emplace_back(2), B.emplace_back(2);
        else if(S[i] == '0') A.emplace_back(0), B.emplace_back(0);
        else if(S[i] == '5') A.emplace_back(2), B.emplace_back(3);
        else A.emplace_back(1), B.emplace_back(S[i] - '0' - 1);
    }
    assert(B.size() != 1 || B[0]);
    while(B.size() > 1 && !B.back()) B.pop_back();
    reverse(A.begin(), A.end()), reverse(B.begin(), B.end());
    printf("Case #%d: ", idx);
    for(int d : A) printf("%d", d);
    printf(" ");
    for(int d : B) printf("%d", d);
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}
