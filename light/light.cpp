#include <iostream>
using namespace std;

const int MAXN = 6;
const int dx [] = {0, 1, 0, -1};
const int dy [] = {1, 0, -1, 0};

int n;

int a [MAXN][MAXN];
int sol [MAXN][MAXN];

void dfs (int x, int y) {
    bool flag = 1;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            if (!a [i][j]) {
                flag = 0;
                break;
            }
    if (flag) {
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n; ++ j)
                cout << sol [i][j] << " ";
            cout << endl;
        }
        exit (0);
    }
    
    if (x == n + 1)
        return;

    for (int i = 0; i < 4; ++ i)
        a [x + dx [i]][y + dy [i]] = !a [x + dx [i]][y + dy [i]];
    a [x][y] = !a [x][y];
    sol [x][y] = 1;
    if (y == n)
        dfs (x + 1, 1);
    else
        dfs (x, y + 1);
    
    for (int i = 0; i < 4; ++ i)
        a [x + dx [i]][y + dy [i]] = !a [x + dx [i]][y + dy [i]];
    a [x][y] = !a [x][y];
    sol [x][y] = 0;
    if (y == n)
        dfs (x + 1, 1);
    else
        dfs (x, y + 1);
}

int main () {
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            cin >> a [i][j];
    dfs (1, 1);
    return 0;
}