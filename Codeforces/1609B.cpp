#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, q;
char S[N];

int get_abc(int pos) {
    if (S[pos] == 'a')
        return (S[pos + 1] == 'b' && S[pos + 2] == 'c');
    if (S[pos] == 'b')
        return (S[pos - 1] == 'a' && S[pos + 1] == 'c');
    return (S[pos - 2] == 'a' && S[pos - 1] == 'b');
}

int main() {
    scanf("%d %d %s", &n, &q, S + 2);

    int ans = 0;
    for (int i = 2; i <= n + 1; i++)
        if (S[i] == 'a' && S[i + 1] == 'b' && S[i + 2] == 'c')
            ++ans;

    while (q--) {
        int pos;
        char c;
        scanf("%d %c", &pos, &c);
        ans -= get_abc(pos + 1);
        S[pos + 1] = c;
        ans += get_abc(pos + 1);
        printf("%d\n", ans);
    }

    return 0;
}