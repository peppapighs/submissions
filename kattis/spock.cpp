#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

int T;
vector<iii> vec;
vector<string> moveName = {"rock", "paper", "scissors", "lizard", "Spock"};
int A[5][5] = {
    {2, 0, 1, 1, 0},
    {1, 2, 0, 0, 1},
    {0, 1, 2, 1, 0},
    {0, 1, 0, 2, 1},
    {1, 0, 1, 0, 2}
};

int get() {
    char S[105];
    scanf(" %s", S);
    for(int i = 0; i < 5; i++)
        if(moveName[i][0] == S[0])
            return i;
}

int main() {
    for(int i = 0; i < 127; i++)
        for(int j = 0; j < 127; j++)
            for(int k = 0; k < 127; k++)
                vec.emplace_back(i, j, k);

    scanf("%d", &T);
    while(T--) {
        if(vec.size() != 1) {
            vector<int> win(5);
            for(iii t : vec) {
                int x, a, b; tie(x, a, b) = t;
                for(int i = 0; i < 5; i++)
                    win[i] += (A[i][x % 5] == 1);
            }
            printf("%s\n", moveName[max_element(win.begin(), win.end()) - win.begin()].c_str());
            fflush(stdout);

            int now = get();
            vector<iii> nvec;
            for(iii t : vec) {
                int x, a, b; tie(x, a, b) = t;
                if(x % 5 == now)
                    nvec.emplace_back((a * x + b) % 127, a, b);
            }
            vec = vector<iii>(nvec);
        } else {
            int x, a, b; tie(x, a, b) = vec[0];
            for(int i = 0; i < 5; i++) if(A[x % 5][i] == 0) {
                printf("%s\n", moveName[i].c_str());
                fflush(stdout);
                break;
            }
            vec[0] = iii((a * x + b) % 127, a, b);
            get();
        }
    }

    return 0;
}