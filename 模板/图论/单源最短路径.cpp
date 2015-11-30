//label set algorithm

struct Node         // 要丟進Priority Queue的點
{
    int a, d;   // a是點，d是可能的最短路徑長度。
                // p可以提出來，不必放在Node裡。
 
    // constructor，方便建立Vertex物件，方便編寫程式碼。
    Node(int a, int d): a(a), d(d)
    {
        /* empty */
    }
 
    // C++ STL內建的Priority Queue是Max-Heap，不是Min-Heap，
    // 故必須改寫一下比大小的函式。
    bool operator<(const Node& n) const
    {
        return d > n.d;
    }
};
 
int w[9][9];
int d[9];
int parent[9];
bool visit[9];
 
void dijkstra_with_priority_queue(int source)
{
    for (int i=0; i<9; i++) visit[i] = false;
    for (int i=0; i<9; i++) d[i] = 1e9;
 
    parent[source] = source;
 
    priority_queue<Node> PQ;    // C++ STL的Priority Queue
    PQ.push( Node(source, 0) ); // 放入起點
 
    for (int i=0; i<9; i++)
    {
        // 找出下一個要加入到最短路徑樹的點
        Node n;
        while (!PQ.empty())
        {
            n = PQ.top();   PQ.pop();
            if (!visit[n.a]) break;
        }
 
        // 與起點相連通的最短路徑都已找完
        if (PQ.empty()) break;
 
        int a = n.a;
        d[a] = n.d;
        visit[a] = true;
 
        // 將比大小的工作交由Priority Queue來做
        for (int b=0; b<9; b++)
            if (!visit[b] && d[a] + w[a][b] < d[b])
            {
                d[b] = d[a] + w[a][b];
                parent[b] = a;
                PQ.push( Node(b, d[a] + w[a][b]) );
            }
    }
}

//wrap this algorithm in class
class shortest_path{

    struct Node         // 要丟進Priority Queue的點
    {
        int a;
        LL d;   // a是點，d是可能的最短路徑長度。
                    // p可以提出來，不必放在Node裡。
     
        // constructor，方便建立Vertex物件，方便編寫程式碼。
        Node(int a, LL d): a(a), d(d)
        {
            /* empty */
        }
     
        // C++ STL內建的Priority Queue是Max-Heap，不是Min-Heap，
        // 故必須改寫一下比大小的函式。
        bool operator<(const Node& n) const
        {
            return d > n.d;
        }
    };

public:
    void dijkstra_with_priority_queue(int source,vector<Edge>*mp,LL* d,int n){
        vector<bool>reach(n+1);

        priority_queue<Node> PQ;    // C++ STL的Priority Queue
            PQ.push( Node(source, 0) ); // 放入起點

            for (int i=0; i<n; i++)
        {
                
                    // 找出下一個要加入到最短路徑樹的點
                    Node n;
                    while (!PQ.empty())
                    {
                            n = PQ.top();   
                            if (!visit[n.a]) break;
                            PQ.pop();
                    }
         
            // 與起點相連通的最短路徑都已找完
                    if (PQ.empty()) break;

                    PQ.pop();

                    int a = n.a;
                    d[a] = n.d;
                    visit[a] = true;
         
                    // 將比大小的工作交由Priority Queue來做
                    for (int b=0; b<mp[a].size(); b++)
                    {
                        int next=mp[a][b];
                            if (!visit[next] && d[a] + w[a][next] < d[next])
                            {
                                d[next] = d[a] + w[a][next];
                                PQ.push( Node(next, d[a] + w[a][next]) );
                            }
                    }

    }
};


//label correctting algorithm
int w[9][9];    // 一張有權重的圖：adjacency matrix
int d[9];       // 紀錄起點到各個點的最短路徑長度
int parent[9];  // 紀錄各個點在最短路徑樹上的父親是誰
int n[9];       // 記錄各個點被標記幾次，初始化為零。
 
void label_correcting(int source)
{
    memset(n, 0, sizeof(n));    // 初始化
 
    d[source] = 0;              // 設定起點的最短路徑長度
    parent[source] = source;    // 設定起點是樹根（父親為自己）
    n[source]++;                // 起點被標記了一次
 
    queue<int> Q;               // 一個存放點的容器：queue
    Q.push(source);             // 將起點放入容器當中
    
    while (!Q.empty())
    {
        int a = Q.top(); Q.pop();       // 從容器中取出一點，作為a點
 
        for (int b=0; b<9 ++b)
            if (d[a] + w[a][b] < d[b])
            {
                if (++n[b] >= 9) return;// 圖上有負環，最短路徑樹不存在
 
                d[b] = d[a] + w[a][b];  // 修正起點到b點的最短路徑長度
                parent[b] = a;          // b點是由a點延伸過去的
                Q.push(b);              // 將b點放入容器當中
            }
    }
}