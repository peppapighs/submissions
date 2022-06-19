#include <bits/stdc++.h>

using namespace std;

int n = 10, A[105][105];
char S[2005];

int main() {
    for (int i = 1, a, b; i <= 10; i++) {
        scanf("%d %d", &a, &b);
        A[a + 50][b + 50] = 1;
    }
    int x = 50, y = 50;
    A[50][50] = 2;

    scanf(" %s", S + 1);
    for (int i = 1; S[i] != '\0'; i++) {
        if (S[i] == 'L') {
            int nx = x, ny = y, cur = 2;
            A[x][y] = 0;
            --x;
            while (true) {
                swap(cur, A[--nx][ny]);
                if (cur == 0)
                    break;
            }
        } else if (S[i] == 'R') {
            int nx = x, ny = y, cur = 2;
            A[x][y] = 0;
            ++x;
            while (true) {
                swap(cur, A[++nx][ny]);
                if (cur == 0)
                    break;
            }
        } else if (S[i] == 'U') {
            int nx = x, ny = y, cur = 2;
            A[x][y] = 0;
            ++y;
            while (true) {
                swap(cur, A[nx][++ny]);
                if (cur == 0)
                    break;
            }
        } else {
            int nx = x, ny = y, cur = 2;
            A[x][y] = 0;
            --y;
            while (true) {
                swap(cur, A[nx][--ny]);
                if (cur == 0)
                    break;
            }
        }
    }
    printf("(%d %d)\n", x - 50, y - 50);
    for (int j = 10; j >= -10; j--) {
        for (int i = -10; i <= 10; i++)
            printf("%d", A[i + 50][j + 50]);
        printf("\n");
    }

    return 0;
}