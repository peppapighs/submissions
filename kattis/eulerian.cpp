#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m;
int in[N], out[N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        ++out[a], ++in[b];
    }
    vector<int> st, en;
    for (int i = 1; i <= n; i++) {
        if (out[i] == in[i] + 1)
            st.emplace_back(i);
        else if (in[i] == out[i] + 1)
            en.emplace_back(i);
        else if (in[i] != out[i])
            return !printf("no\n");
    }
    if (st.size() == 1 && en.size() == 1)
        printf("%d %d\n", st[0], en[0]);
    else if (st.empty() && en.empty())
        printf("anywhere\n");
    else
        printf("no\n");

    return 0;
}