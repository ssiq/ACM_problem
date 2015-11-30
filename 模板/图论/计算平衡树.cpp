bool adj[9][9];         // adjacency matrix，儲存一棵樹。
int p[9];               // DFS tree
int h1[9], h2[9];       // 紀錄最高與次高的高度
int c1[9], c2[9];       // 紀錄最高與次高的來源
 
void record(int x, int height, int child)
{
    if (height > h1[x])
    {
        h2[x] = h1[x]; c2[x] = c1[x];
        h1[x] = height; c1[x] = child;
    }
    else if (height > h2[x])
    {
        h2[x] = height; c2[x] = child;
    }
}
 
void DFS1(int x)
{
    h1[x] = h2[x] = 0;
    for (int y=0; y<9; ++y)
        if (adj[x][y])
            if (y != p[x])
            {
                p[y] = x;
                DFS1(y);
                record(x, h1[y] + 1, y);
            }
            else
                ;   // 只能留待下一波解決
}
 
void DFS2(int x)
{
    if (p[x] != x)  // 樹根沒有父親，不必算。
    {
        int y = p[x];   // 上一波沒解決的部分
 
        // 記錄次高的高度，用意在於這裡！
        if (c1[y] != x)
            record(x, h1[y] + 1, y);
        else
            record(x, h2[y] + 1, y);
    }
 
    for (int y=0; y<9; ++y)
        if (adj[x][y])
            if (y != p[x])
                DFS2(y);
}
 
void balanced_height()
{
    int root = 0;   // 隨便挑一點當作樹根
    p[root] = root;
    DFS1(root);
    DFS2(root);
 
    int b_height = 1e9;
    int diameter = 0;   // 順便算直徑
    for (int x=0; x<9; ++x)
    {
        b_height = min(b_height, h1[x]);
        diameter = max(diameter, h1[x]);
    }
    cout << "樹經過平衡之後的高度是" << b_height;
    cout << "樹的直徑是" << diameter;
 
    for (int x=0; x<9; ++x)
        if (h1[x] == b_height)
            cout << "可以作為樹根的點為" << x;
 
    for (int x=0; x<9; ++x)
        if (h1[x] == diameter)
            cout << "可作為直徑的端點有" << x;
}