bool adj[9][9];
int diameter = 0;
 
int DFS(int x, int px)  // px是x的父親
{
    int h1 = 0, h2 = 0; // 紀錄最高與次高的高度
    for (int y=0; y<9; ++y)
        if (adj[x][y] && y != px)
        {
            int h = DFS(y, x) + 1;
            if (h > h1) h2 = h1, h1 = h;
            else if (h > h2) h2 = h;
        }
    diameter = max(diameter, h1 + h2);
    return h1;
}
 
void tree_diameter()
{
    diameter = 0;   // 初始化
 
    int root = 0;   // 隨便選一個樹根
    DFS(root, root);
    cout << "樹的直徑是" << diameter;
}