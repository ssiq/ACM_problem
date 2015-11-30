bool adj[9][9];
 
int DFS(int x, int px)  // px是x的父親
{
    int h = 0;  // 紀錄最高的高度
    for (int y=0; y<9; ++y)
        if (adj[x][y] && y != px)
            h = max(h, DFS(y, x) + 1);
    return h;
}
 
void tree_height(int root)
{
    cout << "樹的高度是" << DFS(root, root);
}