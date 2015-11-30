bool adj[100][100]; // adjacency matrix，儲存一棵樹，假設樹根為第0點。
bool visit[100];    // DFS當下已拜訪過的點
int lca[100][100];  // 任兩點之間的LCA
 
int find(int x)
{
    return x == p[x] ? x : (p[x] = find(p[x]));
}
 
int DFS(int x)
{
    visit[x] = true;
    for (int y=0; y<100; ++y)
        if (visit[y])
            lca[x][y] = lca[y][x] = find(y);
 
    for (int y=0; y<100; ++y)
        if (!visit[y])
        {
            DFS(y);
            p[y] = x;   // union(y, x)，並讓x是樹根
        }
}
 
int main()
{
    for (int i=0; i<100; ++i) p[i] = i;
 
    for (int i=0; i<100; ++i) visit[i] = false;
    DFS(0); // 假設樹根為0
    
    int x, y;
    while (cin >> x >> y)
        cout << "x點與y點的LCA是" << lca[x][y];
    return 0;
}