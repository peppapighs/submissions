#include <bits/stdc++.h>

using namespace std;

int ask(int a, int b, int ret = 0) {
    printf("? %d %d\n", a, b);
    fflush(stdout);
    scanf("%d", &ret);
    return ret;
}

vector<int> ans = {4, 8, 15, 16, 23, 42};

int a[6];

int main() {
    for (int i = 1; i <= 4; i++)
        a[i] = ask(i, i + 1);
    do {
        bool valid = true;
        for (int i = 1; i <= 4; i++)
            if (ans[i - 1] * ans[i] != a[i])
                valid = false;
        if (!valid)
            continue;
        printf("! ");
        for (int i : ans)
            printf("%d ", i);
        printf("\n");
        fflush(stdout);
    } while (next_permutation(ans.begin(), ans.end()));

    return 0;
}