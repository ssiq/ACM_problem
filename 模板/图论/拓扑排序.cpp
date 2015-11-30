//part1 adjacency matrix
bool map[9][9]; // adjacency matrix
int ref[9];     // 紀錄圖上每一個點目前仍被多少條邊連到
 
void topological_sort()
{
    for (int i=0; i<9; ++i) ref[i] = 0; // 初始化為0
 
    // 累計圖上每一個點被幾條邊連到
    for (int i=0; i<9; ++i)
        for (int j=0; j<9; ++j)
            if (map[i][j])
                ref[j]++;
 
    // 開始找出一個合理的排列順序
    for (int i=0; i<9; ++i)
    {
        // 尋找沒有被任何邊連向的點
        int s = 0;
        while (s < 9 && ref[s] != 0) ++s;
 
        if (s == 9) break;  // 找不到。表示目前殘存的圖是個環。
        ref[s] = -1;        // 設為已找過（刪去s點）
 
        cout << s;          // 印出合理的排列順序的第i點
 
        // 更新ref的值（刪去由s點連出去的邊）
        for (int t=0; t<9; ++t)
            if (map[s][t])
                ref[t]--;
    }
}

//part2 adjacency lists
int map[9][9], size[9]; // adjacency lists
int ref[9];     // 紀錄圖上每一個點目前仍被多少條邊連到
 
void topological_sort()
{
    for (int i=0; i<9; ++i) ref[i] = 0; // 初始化為0
 
    // 累計圖上每一個點被幾條邊連到
    for (int i=0; i<9; ++i)
        for (int j=0; j<size[i]; ++j)
            ref[map[i][j]]++;
 
    // 宣告一個queue來紀錄已經沒有被任何邊連向的點
    queue<int> Q;
    for(int i=0;i<9;++i)
    {
        if(!ref(i))Q.push(i);
    }
 
    // 開始找出一個合理的排列順序
    for (int i=0; i<9; ++i)
    {
        // 尋找沒有被任何邊連向的點
        if (Q.empty()) break;       // 找不到。表示目前殘存的圖是個環。
        int s = Q.front(); Q.pop();
        ref[s] = -1;                // 設為已找過（刪去s點）
 
        cout << s;                  // 印出合理的排列順序的第i點
 
        // 更新ref的值（刪去由s點連出去的邊）
        for (int j=0; j<size[s]; ++j)
        {
            int t = map[s][j];
            ref[t]--;
            if (!ref[t]) Q.push(t); // 紀錄已經沒有被任何邊連向的點
        }
    }
}


//part3 DFS
bool map[9][9];     // adjacency matrix
int visit[9];       // 記錄DFS遍歷過的點
int order[9], n;    // 儲存一個合理的排列順序
 
bool cycle;         // 記錄DFS的過程中是否偵測到環
 
void DFS(int s)
{
    // back edge，有環。
    if (visit[s] == 1) cycle = true;
    // forward edge、cross edge。
    if (visit[s] == 2) return;
 
    visit[s] = 1;
    for (int t=0; t<9; ++t)
        DFS(t);
    visit[s] = 2;
 
    order[n--] = s;     // 記錄合理的排列順序
}
 
void topological_sort()
{
    // 初始化
    for (int i=0; i<9; i++) visit[i] = 0;
    cycle = false;
    n = 9-1;
    
    // 進行DFS
    for (int s=0; s<9; ++s)
        if (!visit[s])
            DFS(s);
 
    // 輸出結果
    if (cycle)
        cout << "圖上有環";
    else
        // 印出一個合理的排列順序
        for (int i=0; i<9; ++i)
            cout << order[i];
}