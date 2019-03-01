#include <bits/stdc++.h>

using namespace std;

int n;
map<int, int> pos[10];
vector<int> V;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= 5; i++) for(int j = 1, a; j <= n; j++) {
        scanf("%d", &a);
        pos[i][a] = j; 
        if(i == 1) V.emplace_back(a);
    }
    sort(V.begin(), V.end(), [&](const int &a, const int &b) {
        int cnt = 0;
        for(int i = 1; i <= 5; i++) cnt += (pos[i][a] < pos[i][b]);
        return 3 <= cnt;
    });
    for(int i : V) printf("%d\n", i);

    return 0;
}