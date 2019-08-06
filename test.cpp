#include <bits/stdc++.h>

using namespace std;

int a[3][3], turn;

void print() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(a[i][j] == 0) printf("- ");
            if(a[i][j] == 1) printf("X ");
            if(a[i][j] == 2) printf("O ");
        }
        printf("\n");
    }
    printf("\n");
}

bool chk() {
    for(int i = 0; i < 3; i++) if(a[i][0] && a[i][1] && a[i][2] && a[i][0] == a[i][1] && a[i][1] == a[i][2])
        return true;
    for(int i = 0; i < 3; i++) if(a[0][i] && a[1][i] && a[2][i] && a[0][i] == a[1][i] && a[1][i] == a[2][i])
        return true;
    if(a[0][0] && a[1][1] && a[2][2] && a[0][0] == a[1][1] && a[1][1] == a[2][2]) return true;
    if(a[0][2] && a[1][1] && a[2][0] && a[0][2] == a[1][1] && a[1][1] == a[2][0]) return true;
    return false;
}

pair<int, int> search(int cnt) {
    pair<int, int> ret(0, 0);
    if(chk() && turn % 2) return pair<int, int>(1, 0);
    else if(chk() && turn % 2 != 0) return pair<int, int>(0, 1);
    if(cnt != 9) {
	    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(!a[i][j]) {
	        ++turn, a[i][j] = (turn % 2 ? 1 : 2);
	        pair<int, int> p = search(cnt + 1);
	        --turn, a[i][j] = 0;
	        ret.first += p.first, ret.second += p.second;
	    }
	}
    return ret;
}

int main() {
    srand(time(NULL));

    printf("=========== Tic Tac Toe =============\n");
    printf("You are (X), Your opponent is (O)\n");
    if(turn = rand() % 2) printf("You start first!\n");
    else printf("Opponent start first!\n");

    while(true) {
        if(chk()) {
            if(turn % 2) printf("You lose!\n");
            else printf("You win!\n");
            exit(0);
        }
        int cnt = 0;
        for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) cnt += (a[i][j] != 0);
        if(cnt == 9) {
            printf("Draw!\n");
            exit(0);
        }
        print();
        if(turn % 2) {
            printf("Enter your next move :\n");
            int r, c;
            while(true) {
                printf("Row (1-3) : ");
                scanf("%d", &r);
                if(r < 1 || r > 3) {
                    printf("Row is out of bound\n");
                    continue;
                }
                printf("Column (1-3) : ");
                scanf("%d", &c);
                if(c < 1 || c > 3) {
                    printf("Column is out of bound\n");
                    continue;
                }
                if(a[r][c]) {
                    printf("Cell is occupied\n");
                    continue;
                }
                break;
            }
            a[--r][--c] = 1;
        } else {
			double mxprob = 0;
			int r = 0, c = 0, cnt = 0;
            for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) cnt += (a[i][j] != 0);
			for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(!a[i][j]) {
                a[i][j] = 2, ++turn;
                pair<int, int> p = search(cnt + 1);
                a[i][j] = 0, --turn;
                double now = (double)(p.first) / (double)(p.first + p.second);
                if(now > mxprob) mxprob = now, r = i, c = j;
            }
            printf("max prob : %lf\n", mxprob);
            a[r][c] = 2;
        }
        ++turn;
    }

    return 0;
}
