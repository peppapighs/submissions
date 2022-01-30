#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 105;

bool compare(string a, string b) {
    if(a == b) return true;
    if(a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

int n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    vector<string> A(n + 1);
    for(int i = 1; i <= n; i++) cin >> A[i];

    vector<string> ans;
    vector<string> tmp(A.begin(), A.end());
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < tmp[i].size(); j++) {
            for(int k = '0'; k <= '9'; k++) {
                if(k == '0' && j == 0 && tmp[i].size() != 1)
                    continue;
                tmp[i][j] = k;
                bool valid = true;
                for(int l = 1; l < n; l++) valid &= compare(tmp[l], tmp[l + 1]);
                if(!valid) ans = tmp;
                tmp[i][j] = A[i][j];
            }
        }
    }
    if(ans.empty()) cout << "impossible\n";
    else {
        for(int i = 1; i <= n; i++) cout << ans[i] << " ";
        cout << "\n";
    }

    return 0;
}