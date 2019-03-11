#include <bits/stdc++.h>

using namespace std;

const int N = 3e3+5;

struct num {
    char a, b, c;
    num() { }
    num(char a, char b, char c) : a(a), b(b), c(c) { }
    void inc() {
        ++c;
        if(c == 100) c = 0, ++b;
        if(b == 100) b = 0, ++a;
    }
    int conv() {
        return a * 10000 + b * 100 + c;
    }
    friend num operator+(const num &a, const num &b) {
        int n1 = (int)a.a + (int)b.a;
        int n2 = (int)a.b + (int)b.b;
        int n3 = (int)a.c + (int)b.c;
        n2 += n3 / 100, n3 %= 100;
        n1 += n2 / 100, n2 %= 100;
        return num(n1, n2, n3);
    }
    friend num operator-(const num &a, const num &b) {
        int n1 = (int)a.a - (int)b.a;
        int n2 = (int)a.b - (int)b.b;
        int n3 = (int)a.c - (int)b.c;
        while(n3 < 0) n3 += 100, --n2;
        while(n2 < 0) n2 += 100, --n1;
        return num(n1, n2, n3);
    }
};

int n, m;
num dp[4][N][N];

int get(int k, int a, int b, int c, int d) {
    return dp[k][c][d].conv() + dp[k][a-1][b-1].conv() - dp[k][a-1][d].conv() - dp[k][c][b-1].conv();
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b, c, d; i <= n; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        dp[0][a][b].inc(), dp[1][a][d].inc();
        dp[2][c][b].inc(), dp[3][c][d].inc();
    }
    for(int k = 0; k < 4; k++) for(int i = 1; i <= 3000; i++) for(int j = 1; j <= 3000; j++)
        dp[k][i][j] = dp[k][i][j] + dp[k][i-1][j] + dp[k][i][j-1] - dp[k][i-1][j-1];
    for(int i = 1, a, b, c, d; i <= m; i++) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        int sum = get(2, a, d+1, 3000, 3000) + get(0, c+1, 1, 3000, d);
        sum += get(3, 1, b, a-1, 3000) + get(1, 1, 1, c, b-1);
        printf("%d\n", n - sum);
    } 

    return 0;
}