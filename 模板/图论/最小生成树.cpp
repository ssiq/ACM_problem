//Prim algorithm
int w[9][9];    // 一張有權重的圖
int d[9];       // 紀錄目前的MST到圖上各點的距離。
int parent[9];  // 紀錄各個點在MST上的父親是誰
bool visit[9];  // 紀錄各個點是不是已在MST之中
 
void prim()
{
    for (int i=0; i<9; i++) visit[i] = false;
    for (int i=0; i<9; i++) d[i] = 1e9;
 
    d[0] = 0;   // 可以選定任何點做為樹根，這裡以第零點做為樹根。
    parent[0] = 0;
 
    for (int i=0; i<9; i++)
    {
        int a = -1, b = -1, min = 1e9;
        for (int j=0; j<9; j++)
            if (!visit[j] && d[j] < min)
            {
                a = j;  // 記錄這一條邊
                min = d[j];
            }
 
        if (a == -1) break; // 與起點相連通的MST都已找完
        visit[a] = true;
 
        for (b=0; b<9; b++)
            // 以下與Dijkstra's Algorithm略有不同
            if  (!visit[b] && w[a][b] < d[b])
            {
                d[b] = w[a][b]; // 離樹最近，不是離根最近。
                parent[b] = a;
            }
    }
}

//Kruskal algorithm
struct Edge
{
    int a, b, c;    // 起點，終點，權重。
 
    // 用於比大小的函式
    bool operator<(const Edge& e) const
    {
        return c < e.c;
    }
};
 
// edges[]存放著圖上所有邊，E為邊的總數，V為點的總數。
void Kruskal(Edge edges[], int E, int V)
{
    DisjointSets sets;          // Disjoint Sets
 
    std::sort(edges, edges+E);  // Quick Sort
                                // 將圖上所有邊依照權重大小，由小到大排序。
    int i, j;
    for (i = 0, j = 0; i < V-1 && j < E; ++i)   // 找出V-1條邊
    {
        // 擷取出最短的、不會造成環的邊
        while (sets.find(edges[j].a, edges[j].b)) j++;
 
        // 連結選到的邊
        sets.union(edges[j].a, edges[j].b);
 
        // 印出選到的edge
        cout << "起點：" << edges[j].a
            << "終點：" << edges[j].b
            << "權重：" << edges[j].c;
 
        j++;    // 別忘記累計索引值
    }
 
    if (i != V-1) cout << "MST不存在!";
}

//Borůvka's Algorithm
pass


//DAG's minnum spanning tree
int V, E;
struct Edge {int a, b, c;} Ed[40000];
int d[1000], p[1000], v[1000], n[1000], m[1000];
// 每個點最小入邊的權重，每個點最小入邊的來源，
// 拜訪過，水母環，已收縮。
 
int MST(int r)
{
    memset(m, 0, sizeof(m));
 
    // 目前生成樹的權重，累計收縮水母環而失去的權重。
    int w1 = 0, w2 = 0; 
    while (true)    // 一旦形成生成樹就停止。最多執行V-1次。
    {
        /* O(E) graph traversal.
           find minimum in-edge for each vertice.
 
           --->o
        */
        memset(d, 1, sizeof(d));
        memset(p, -1, sizeof(p));
 
        for (int i=0; i<E; ++i)
        {
            int &a = Ed[i].a, &b = Ed[i].b, &c = Ed[i].c;
            if (a != b && b != r && c < d[b])
                d[b] = c, p[b] = a;
        }
 
        /* O(V) jellyfish detection
             ___
            /   \
            \___/
           _/|||\_
            //1\\
        */
        memset(v, -1, sizeof(v));
        memset(n, -1, sizeof(n));
 
        w1 = 0;
        bool jf = false;
        for (int i=0; i<V; ++i)
        {
            if (m[i]) continue;
            if (p[i] == -1 && i != r) return 1e9;
            if (p[i] >= 0) w1 += d[i];
 
            // 找水母環
            int s;
            for (s = i; s != -1 && v[s] == -1; s = p[s])
                v[s] = i;
 
            // 標記水母環上的點，以及將會被收縮掉的點。
            if (s != -1 && v[s] == i)
            {
                jf = true;
                int j = s;
                do
                {
                    n[j] = s; m[j] = 1;
                    w2 += d[j]; j = p[j];
 
                } while (j != s);
                m[s] = 0;
            }
        }
        if (!jf) break;
 
        /* O(E) edge reweighting and cycle contraction
             ___
            /   \ <-
            \___/
        */
        for (int i=0; i<E; ++i)
        {
            int &a = Ed[i].a, &b = Ed[i].b, &c = Ed[i].c;
            if (n[b] >= 0) c -= d[b];
            if (n[a] >= 0) a = n[a];
            if (n[b] >= 0) b = n[b];
            if (a == b) Ed[i--] = Ed[--E];
        }
}
    return w1 + w2;
}