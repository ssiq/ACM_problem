//part1

int V = 100;        // 圖上有100點。
bool map[100][100]; // 一張圖，adjacency matrix。
int visit[100];     // 紀錄各個點進行DFS的遍歷順序。
                    // 可用來判斷祖先和子孫。
int a[100]; // 紀錄各棵子樹可回到哪個祖先，而且越老越好。
            // 例如以樹根為第4點的子樹當中，
            // 存在著點，可藉由back edges回到第a[4]點。
 
void DFS(int s, int p, int& n)  // 第p點是第s點的父親
{                               // n是遍歷順序值。
    visit[s] = n++; // 紀錄遍歷順序
    a[s] = s;   // 預設為沒有back edge（最多只能回到自己之意）
 
    int child = 0;      // 紀錄第s點有幾個小孩
    bool ap = false;    // 紀錄第s點是不是關節點
 
    for (int t=0; t<N; ++t)         // 往DFS trees的深處走
        if (map[s][t] && t != p)    // 避免回頭路
            if (visit[t])   // back edge
            {
                // 紀錄越老的祖先越好
                if (visit[t] < visit[a[s]]) a[s] = t;
            }
            else            // child
            {
                child ++;
                DFS(t, s, n);
 
                // 第s點為根的子樹，
                // 或許可以經過第t點以下的點的back edges，
                // 回到第s點的祖先。紀錄之。
                if (visit[a[t]] < visit[a[s]]) a[s] = a[t];
 
                // 樹根為第t點的子樹不能回到第s點的祖先。
                if (!(visit[a[t]] < visit[s])) ap = true;
            }
 
    // 判斷是不是關節點。樹根和非樹根分開判斷。
    if (s == p && child > 1 || s != p && ap)
        cout << "第" << s << "點是關節點" << endl;
}
 
int articulation_vertex()
{
    memset(visit, 0, sizeof(visit));
 
    int n = 1;
    for (int s=0; s<V; ++s) // 進行DFS
        if (!visit[s])
            DFS(s, s, n);
}


//part2

int va[100];    // 紀錄各個子樹可回到哪個祖先，而且越前面越好。
                // 例如以第4點為樹根的子樹當中，
                // 有點可藉由back edges回到遍歷順序為a[4]的點。
 
void DFS(int s, int p, int& n)
{
    va[s] = visit[s] = n++;
 
    int child = 0;
    bool ap = false;
 
    for (int t=0; t<N; ++t)
        if (map[s][t] && t != p)
            if (visit[t])   // back edge
                // 紀錄遍歷順序值較小的
                va[s] = min(va[s], visit[t]);
            else            // child
            {
                child ++;
                DFS(t, s, n);
 
                // 紀錄遍歷順序值較小的
                va[s] = min(va[s], va[t]);
                if (va[t] >= visit[s]) ap = true;
            }
 
    if (s == p && child > 1 || s != p && ap)
        cout << "第" << s << "點是關節點" << endl;
}

//part3

int DFS(int s, int p, int& n)
{
    int vas = visit[s] = n++;
 
    int child = 0;
    bool ap = false;
 
    for (int t=0; t<N; ++t)
        if (map[s][t] && t != p)
            if (visit[t])   // back edge
                // 紀錄遍歷順序值較小的
                vas = min(vas, visit[t]);
            else            // child
            {
                child ++;
                int vat = DFS(t, s, n);
 
                // 紀錄遍歷順序值較小的
                vas = min(vas, vat);
                if (vat >= visit[s]) ap = true;
            }
 
    if (s == p && child > 1 || s != p && ap)
        cout << "第" << s << "點是關節點" << endl;
 
    return vas;
}