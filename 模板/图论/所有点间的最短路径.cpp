//part1 do not kown the path
int w[9][9];    // 一張有權重的圖
int d[9][9];    // 最短路徑長度
 
void Floyd_Warshall()
{
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
            d[i][j] = w[i][j];
 
    for (int k=0; k<9; k++)     // 嘗試每一個中繼點
        for (int i=0; i<9; i++) // 計算每一個i點與每一個j點
            for (int j=0; j<9; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
}

//part2
int w[9][9];
int d[9][9];
int medium[9][9];   // 由i點到j點的路徑，其中繼點為medium[i][j]。
 
void Floyd_Warshall()
{
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
        {
            d[i][j] = w[i][j];
            medium[i][j] = -1;  // 預設為沒有中繼點
        }
 
    for (int k=0; k<9; k++)
        for (int i=0; i<9; i++)
            for (int j=0; j<9; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    medium[i][j] = k;   // 由i點走到j點經過了k點
                }
}
 
// 這支函式並不會印出起點和終點，必須另行印出。
void find_path(int i, int j)        // 印出由i點到j點的最短路徑
{
    if (medium[i][j] == -1) return; // 沒有中繼點就結束
 
    find_path(i, medium[i][j]);     // 先把前面的路徑都印出來
    cout << medium[i][j] << endl;   // 再把中繼點印出來
    find_path(medium[i][j], j);     // 最後把後面的路徑都印出來
}




//part3
int w[9][9];
int d[9][9];
int next[9][9]; // 由i點到j點的路徑，第二點為next[i][j]。
 
void Floyd_Warshall()
{
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
        {
            d[i][j] = w[i][j];
            next[i][j] = j; // 一開始沒有中繼點，所以第二點就是終點。
        }
 
    for (int k=0; k<9; k++)
        for (int i=0; i<9; i++)
            for (int j=0; j<9; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
 
                    //由i點到j點的路徑的第二點，
                    // 正是由i點到k點的路徑的第二點。
                    next[i][j] = next[i][k];
                }
}
 
void find_path(int i, int j)        // 印出由i點到j點的最短路徑
{
    cout << i << endl;              // 先把起點印出來
    if (i != j)                     // 當還有中繼點的時候
        find_path(next[i][j], j);   // 再把第二點以後的路徑都印出來
}


//偵測負環（adjacency matrix）
bool negative_cycle()
{
    for (int i=0; i<9; i++)
        if (d[i][i] < 0)
            return true;
    return false;
}