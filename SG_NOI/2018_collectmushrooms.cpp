#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int R, C, d, k;
int A[N], ans;
vector<int> mush;

int get(int r, int c) { return r*C + c; }

int main() {
    scanf("%d %d %d %d", &R, &C, &d, &k);
    for(int i = 1; i <= R; i++) {
        char S[N];
        scanf(" %s", S+1);
        for(int j = 1; j <= C; j++) {
            if(S[j] == 'M') mush.emplace_back(get(i, j));
            else if(S[j] == 'S') {
                ++A[get(max(1, i-d), max(1, j-d))];
                --A[get(min(R+1, i+d+1), max(1, j-d))];
                --A[get(max(1, i-d), min(C+1, j+d+1))];
                ++A[get(min(R+1, i+d+1), min(C+1, j+d+1))];
            }
        }
    }
    for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) 
        A[get(i, j)] += A[get(i-1, j)] + A[get(i, j-1)] - A[get(i-1, j-1)];
    for(int m : mush) if(A[m] >= k) ++ans;
    printf("%d\n", ans);

    return 0;
}