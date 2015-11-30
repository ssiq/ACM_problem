bool map[9][9]; // 一張圖，資料結構為adjacency matrix。
bool tc[9][9];  // Transitive Closure
 
void warshall()
{
    // 先把原圖複製到要進行DP計算的陣列
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
            tc[i][j] = map[i][j];
 
    for (int k=0; k<9; k++) // 嘗試每一個中繼點
        for (int i=0; i<9; i++) // 計算每一個i點與每一個j點
            for (int j=0; j<9; j++)
                if (tc[i][k] && tc[k][j])
                    tc[i][j] = true;
}