bool w[9][9];   // adjacency matrix
int topo[9];    // 經過拓樸排序後的順序
int parent[9];  // 紀錄各個點在最短路徑樹上的父親是誰
 
void shortest_path_tree(int source)
{
    for (int i=0; i<9; i++) visit[i] = false;
    for (int i=0; i<9; i++) d[i] = 1e9;
 
    // 找出起點是在拓樸排序中的哪一個位置
    int p = 0;
    while (p < 9 && topo[p] != source) p++;
 
    // 計算最短路徑長度
    d[p] = 0;       // 設定起點的最短路徑長度
    parent[p] = p;  // 設定起點是樹根（父親為自己）
 
    for (int i=p; i<9; ++i) // 看看每一個點可連向哪些點
        for (int j=i+1; j<9; ++j)
        {
            int a = topo[i], b = topo[j];
            if (d[a] + w[a][b] < d[b])
            {
                d[b] = d[a] + w[a][b];
                parent[b] = a;
            }
        }
}

//迴圈的部分還有另一種寫法。
for (int j=p+1; j<9; ++j)   // 看看每一個點被哪些點連向
        for (int i=0; i<j; ++i)
        {
            int a = topo[i], b = topo[j];
            if (d[a] + w[a][b] < d[b])
            {
                d[b] = d[a] + w[a][b];
                parent[b] = a;
            }
        }
