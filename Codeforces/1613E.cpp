#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m, lx, ly;

void solve() {
    scanf("%d %d", &n, &m);
    vector<string> A;
    for(int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        A.emplace_back(str);
    }
    vector<vector<int>> nb(n, vector<int>(m));
    vector<vector<bool>> win(n, vector<bool>(m));

    auto out = [&](int x, int y) { return x < 0 || x >= n || y < 0 || y >= m; };
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(A[i][j] == 'L') lx = i, ly = j;
        for(int d = 0; d < 4; d++) {
            int nx = i + dx[d], ny = j + dy[d];
            nb[i][j] += !out(nx, ny) && A[nx][ny] != '#';
        }
    }
    
    queue<pii> Q;
    win[lx][ly] = true;
    Q.emplace(lx, ly);
    while(!Q.empty()) {
        pii now = Q.front(); Q.pop();
        for(int i = 0; i < 4; i++) {
            int nx = now.x + dx[i], ny = now.y + dy[i];
            if(out(nx, ny) || A[nx][ny] == '#' || win[nx][ny])
                continue;
            --nb[nx][ny];
            if(nb[nx][ny] <= 1) {
                win[nx][ny] = true;
                Q.emplace(nx, ny);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(A[i][j] == '.') {
                if(win[i][j]) printf("+");
                else printf(".");
            } else printf("%c", A[i][j]);
        }
        printf("\n");
    }
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}