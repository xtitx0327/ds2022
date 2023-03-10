#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 505;
const int INF = 1000000007;

class Graph {
    private:
        /// @brief n, m 分别为图中顶点个数和边的条数
        int n, m;
        /// @brief 图的邻接矩阵
        int arr [MAXN][MAXN];
        /// @brief 两点之间的最短路矩阵
        int dis [MAXN][MAXN];
    public:
        /// @brief 构造函数，图中应有 _n 个结点
        /// @param _n 
        Graph (int _n) {
            this -> n = _n;
            this -> m = 0;
            for (int i = 1; i < MAXN; ++ i)
                for (int j = 1; j < MAXN; ++ j)
                    this -> arr [i][j] = this -> dis [i][j] = INF;
        }

        void addEdge (int u, int v, int w) {
            arr [u][v] = dis [u][v] = w;
            ++ m;
        }

        /// @brief 执行 Bellman-Ford 算法，求出图中任意两点之间的最短路径
        void BellmanFord () {
            for (int i = 1; i <= this -> n; ++ i)
                for (int j = 1; j <= this -> n; ++ j)
                    for (int k = 1; k <= this -> n; ++ k)
                        this -> dis [i][j] = min (this -> dis [i][j], this -> dis [i][k] + this -> dis [k][j]);
        }

        /// @brief 返回结点 u, v 之间的最短路径
        int getResult (int u, int v) {
            return this -> dis [u][v];
        }
};

int main () {
    int n, m, q, u, v, w;
    cin >> n >> m >> q;
    Graph g (n);
    for (int i = 1; i <= m; ++ i) {
        cin >> u >> v >> w;
        g.addEdge (u, v, w);
    }
    g.BellmanFord ();

    for (int i = 1; i <= q; ++ i) {
        cin >> u >> v;
        cout << g.getResult (u, v) << endl;
    }

    return 0;
}