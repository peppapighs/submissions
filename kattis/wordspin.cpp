#include <bits/stdc++.h>

using namespace std;

const int N = 1e7 + 5;

char A[N], B[N];

int main() {
    scanf("%s %s", A + 1, B + 1);

    int ans = 0;
    vector<int> stk;
    for(int i = 1; A[i] != '\0'; i++) {
        int d = B[i] - A[i];
        if(stk.empty()) {
            if(d != 0) stk.emplace_back(d);
        } else {
            if(d == 0 || d / abs(d) != stk.back() / abs(stk.back())) {
                ans += abs(stk.back());
                stk.clear();
                if(d != 0) stk.emplace_back(d);
            } else {
                if(abs(stk.back()) >= abs(d))
                    ans += abs(stk.back() - d);
                while(!stk.empty() && abs(stk.back()) >= abs(d))
                    stk.pop_back();
                stk.emplace_back(d);
            }
        }
    }
    if(!stk.empty()) ans += abs(stk.back());
    printf("%d\n", ans);

    return 0;
}
