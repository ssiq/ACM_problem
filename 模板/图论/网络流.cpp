//Max-Flow: Ford-Fulkerson Algorithm
typedef  int  Graph [ 10 ][ 10 ];   // adjacency matrix
Graph  C ,  F .  R ;               //分别是容量上限、流量、剩余容量
 
int  Ford_Fulkerson ( int  s ,  int  t )     //分别是源点、汇点
{
    memcpy ( R ,  C ,  sizeof ( C ));     //最初每一条边的剩余容量等于容量上限
    memset ( F ,  0 ,  sizeof ( F ));     //最初的流量为零
 
    int  f  =  0 ;   //总流量
    while  (还有augmenting  path )
    {
        int  df  =  augmenting  path  的流量;
        for  (目前的  augmenting  path  中的每一条边( i , j ) )
        {
            F [ i ][ j ] =  F [ i ][ j ] +  df ;
            F [ j ][ i ] = - F [ i ][ j ];
            R [ i ][ j ] =  C [ i ][ j ] -  F [ i ][ j ];
            R [ j ][ i ] =  C [ j ][ i ] -  F [ j ][ i ];
        }
    return  f ;
}

//Max-Flow: Edmonds-Karp Algorithm（Shortest Augmenting Path Algorithm）

typedef  int  Graph [ 10 ][ 10 ];   // adjacency matrix
Graph  C ,  F ,  R ;   //容量上限、流量、剩余容量
bool  visit [ 10 ];  //纪录BFS经过的点
int  path [ 10 ];    //纪录BFS tree
int  flow [ 10 ];    //纪录源点到各个点的流量
                // 用法类似于最短路径演算法的dist阵列
 
int  BFS ( int  s ,  int  t )    //源点与汇点
{
    memset ( visit ,  false ,  sizeof ( visit ));
 
    queue < int >  Q ;
    visit [ s ] =  true ;
    path [ s ] =  s ;
    flow [ s ] =  1e9 ;   //一边找最短路径时，一边计算流量。
    Q . push ( s );
 
    while  (! Q . empty ())
    {
        int  i  =  Q . front ();  Q . pop ();
        for  ( int  j = 0 ;  j < 10 ; ++ j )
            // 在剩余容量的图上找augmenting path
            if  (! visit [ j ] &&  R [ i ][ j ] >  0 )
            {
                visit [ j ] =  true ;
                path [ j ] =  i ;
                flow [ j ] =  min ( flow [ i ],  R [ i ][ j ]);     //容量小的是瓶颈
                Q . push ( j );
 
                if  ( j  ==  t )  return  flow [ t ];
            }
    }
    return  0 ;    //找不到augmenting path了，流量为零。
}
 
int  Edmonds_Karp ( int  s ,  int  t )
{
    memset ( F ,  0 ,  sizeof ( F ));
    memcpy ( R ,  C ,  sizeof ( C ));
 
    int  f ,  df ;   //最大流的流量、扩充路径的流量
    for  ( f = 0 ;  df = BFS ( s ,  t );  f += df )
        // 更新扩充路径上每一条边的流量
        for  ( int  i = path [ t ],  j = t ;  i != j ;  i = path [ j = i ])
        {
            F [ i ][ j ] =  F [ i ][ j ] +  df ;
            F [ j ][ i ] = - F [ i ][ j ];
            R [ i ][ j ] =  C [ i ][ j ] -  F [ i ][ j ];
            R [ j ][ i ] =  C [ j ][ i ] -  F [ j ][ i ];
        }
    return  f ;
}

typedef  int  Graph [ 10 ][ 10 ];   // adjacency matrix
Graph  C ,  F ;                  //容量上限、流量（剩余容量可以相减求得）
int  q [ 10 ],  qf ,  qb ;  p [ 10 ];    // BFS所用的queue
int  p [ 10 ];                   //纪录BFS tree
 
int  Edmonds_Karp ( int  s ,  int  t )
{
    memset ( F ,  0 ,  sizeof ( F ));
 
    int  f  =  0 ;   //最大流的流量
    while  ( true )     //不断找扩充路径直到找不到为止
    {
        // BFS找augmenting path。
        memset ( p , - 1 ,  sizeof ( p ));
        qf  =  qb  =  0 ;
        p [ q [ qb ++] =  s ] =  s ;
 
        while  ( qb  >  qf  &&  p [ t ] == - 1 )
            for  ( int  i = q [ qf ++],  j = 0 ;  j < 10 ; ++ j )
                if  ( p [ j ] == - 1  &&  F [ i ][ j ] -  F [ j ][ i ] <  C [ i ][ j ])
                    p [ q [ qb ++] =  j ] =  i ;
 
        if  ( p [ t ] == - 1 )  break ;
 
        // 更新扩充路径上每一条边的流量
        int  df  =  1e9 ;
        for  ( int  i = p [ t ],  j = t ;  i != j ;  i = p [ j = i ])
            df  <?=  C [ i ][ j ] -  F [ i ][ j ] +  F [ j ][ i ];
        for  ( int  i = p [ t ],  j = t ;  i != j ;  i = p [ j = i ])
            F [ i ][ j ] +=  df ;
        f  +=  df ;
    }
    return  f ;
}

bool  visit [ 10 ];
 
void  DFS ( int  s )
{
    visit [ s ] =  true ;
    for  ( int  t = 0 ;  t < 10 ; ++ t )
        if  (! visit [ t ] &&  F [ s ][ t ] <  C [ s ][ t ])
            DFS ( t ,  N );
}
 
 //利用找出的最大流，从中找出一个最小割（adjacency matrix）
void  find_min_cut ( int  s ,  int  t )
{
    Edmonds_Karp ( s ,  t );
 
    memset ( visit ,  false ,  sizeof ( visit ));
    DFS ( s );
 
    for  ( int  i = 0 ;  i < 10 ; ++ i )     //穷举源点侧的点
        if  ( visit [ i ])
            for  ( int  j = 0 ;  j < 10 ; ++ j )     ​​//穷举汇点侧的点
                if  (! visit [ j ])
                    if  ( C [ i ][ j ] >  0 )     //要确定有边
                        cout  <<  "Cut上的边有"
                            <<  "由"  <<  i  <<  "到"  <<  j  <<  endl ;
}
//找出一个最大流＋计算最大流的权重（adjacency lists）
// adjacency lists当中的一个节点
struct  P
{
    int  t ,  c ,  f ;     //相邻的点、容量上限、流量
    P  * next , * op ;    //另外加入了一个oppsite，用来快速地指向逆向边。
    inline  void  set ( int  _t ,  int  _c ,  int  _f ,  P *  _next ,  P *  _op )
    {
        t  =  _t ;  c  =  _c ;  f  =  _f ;  next  =  _next ;  op  =  _op ;
    }
};
 
// 阴险狡诈的开记忆体方法，
// 如此就不用一直new和delete。
P  m [ 1000000 ];
int  mN  =  0 ;
 
// Edmonds-Karp会用到的记忆体
P *  G [ 3000 + 2 ];            //流量上限
int  q [ 3000 + 2 ],  qf ,  qb ;   // BFS所用的quque
P *  p [ 3000 + 2 ];            //纪录BFS tree
 
// 建立边时，必须同时建立两个方向的边，
// 不然溯洄冲消时会找不到对应的逆向边。
void  add ( int  a ,  int  b ,  int  c )
{
    P *  n1  = & m [ mN ++], * n2  = & m [ mN ++];
    n1 -> set ( b ,  c ,  0 ,  G [ a ],  n2 );
    n2 -> set ( a ,  0 ,  0 ,  G [ b ],  n1 );
    G [ a ] =  n1 ;
    G [ b ] =  n2 ;
}
 
int  Edmonds_Karp ( int  s ,  int  t )
{
    int  f  =  0 ;
    while  ( true )
    {
        memset ( p ,  0 ,  sizeof ( p ));
        qf  =  qb  =  0 ;
        p [ q [ qb ++] =  s ] = ( P *)- 1 ;
 
        while  ( qb  >  qf  && ! ​​p [ t ])
            for  ( P *  n = G [ q [ qf ++]];  n ;  n = n -> next )
                if  (! p [ n -> t ] &&  n -> f  -  n -> op -> f  <  n -> c )
                    p [ q [ qb ++] =  n -> t ] =  n ;
 
        if  (! p [ t ])  break ;
 
        int  df  =  1e9 ;
        for  ( P *  n = p [ t ];  n !=( P *)- 1 ;  n = p [ n -> op -> t ])
            df  <?=  n -> c  -  n -> f  +  n -> op -> f ;
        for  ( P *  n = p [ t ];  n !=( P *)- 1 ;  n = p [ n -> op -> t ])
            n -> f  +=  df ;
        f  +=  df ;
    }
    return  f ;
}

//my produce
struct edge
{
    int from;
    int to;
    // int capacity;
    int flow;
    edge* op;

    void set(int _from,int _to,int _flow,edge* _op)
    {
        from=_from;
        to=_to;
        flow=_flow;
        op=_op;
    }
};

const int max_N=210;
edge epools[max_N<<2];
edge* get_next()
{
    static int last=0;
    return &epools[++last];
}
vector<edge*>mp[max_N];

int  Edmonds_Karp ( int  s ,  int  t )
{
    edge* up[max_N];
    bool reach[max_N];
    int f=0;
    
    while(true)
    {
        memset(up,-1,sizeof(up));
        memset(reach, 0,sizeof(reach));

        queue<int>q;

        up[s]=0;
        reach[s]=true;
        q.push(s);

        while(!reach[t]&&!q.empty())
        {
            int id=q.front();
            DEBUG_OUT("id:"<<id);
            q.pop();
            for(int i=0;i<mp[id].size();++i)
            {
                DEBUG_OUT("i:"<<i);
                edge* next_e=mp[id][i];
                int next=next_e->to;
                if(!reach[next]&&next_e->flow>0)
                {
                    up[next]=next_e;
                    reach[next]=true;
                    q.push(next);
                }
            }
        }

        DEBUG_OUT("end first loop");

        if(!reach[t])break;

        int min_f=MAX_INT;
        for(int i=t;up[i]!=0;i=up[i]->from)
        {
            min_f=min(min_f, up[i]->flow);
        }

        for(int i=t;up[i]!=0;i=up[i]->from)
        {
            up[i]->flow-=min_f;
            up[i]->op->flow+=min_f;
        }

        f+=min_f;

        DEBUG_OUT("f:"<<f);
    }

    return f;
}


//Max-Flow: Capacity Scaling Algorithm
typedef  int  Graph [ 10 ][ 10 ];   // adjacency matrix
Graph  C ,  F ,  Cp ;  //分别是容量上限、流量、逐步添加bit的容量上限
 
void  capacity_scaling ( int  s ,  int  t )
{
    memset ( F ,  0 ,  sizeof ( F ));     //最初的流量为零
    memset ( Cp ,  0 ,  sizeof ( Cp ));   //设为零，然后逐一添加bit到尾端。
 
    int  f  =  0 ;   //总流量
 
    // int有32个bit。
    // 最高位的第32bit用以区分正负值，第31bit才是正整数的最高位。
    // 第1bit向左位移30位到第31bit，就是正整数的最高位。
    for  ( int  b = 1 << 30 ;  b ;  b >>= 1 )
    {
        // 图上每条边都要添加bit或者是加倍
        for  ( int  i = 0 ;  i < 10 ; ++ i )
            for  ( int  j = 0 ;  j < 10 ; ++ j )
            {
                // 添加bit到容量上限数值的尾端
                ( Cp [ i ][ j ] <<=  1 ) += !!( C [ i ][ j ] &  b );
// int d = ( (C[i][j] & b) > 0 ? 1 : 0 );
// tC[i][j] << 1; tC[i][j] += d;
 
                // 将目前的流量加倍
                F [ i ][ j ] <<=  1 ;
            }
        }
 
        f  <<=  1 ;
        f  +=  Ford_Fulkerson ( s ,  t ,  F ,  Cp );    //计算当前最大流
    }
    return  f ;
}

//Max-Flow: Preflow-Push-Relabel Algorithm
typedef  int  Graph [ 10 ][ 10 ];   // adjacency matrix
Graph  C ,  F ;                  //容量上限、流量
int  d [ 10 ],  e [ 10 ];            //高度、含水点的含水量
int  q [ 150 ], * qf , * qb ;        //存放图上所有除源点和汇点外的含水点
 
void  preflow ( int  s ,  int  t )
{
    for  ( int  j = 0 ;  j < N ; ++ j )
        if  ( C [ s ][ j ])
        {
            e [ j ] =  C [ s ][ j ];
            F [ s ][ j ] =  e [ j ];  F [ j ][ s ] = - e [ j ];
            if  ( j  !=  s  &&  j  !=  t ) * qb ++ =  j ;
        }
}
 
void  push ( int  i ,  int  j )
{
    // 水量要足，且不得超过剩余容量。
    int  f  =  min ( e [ i ],  C [ i ][ j ] -  F [ i ][ j ]);
    e [ i ] -=  f ;  e [ j ] +=  f ;
    F [ i ][ j ] +=  f ;  F [ j ][ i ] -=  f ;
}
 
void  relabel ( int  i )
{
    for  ( int  j = 0 ;  j < 10 ; ++ j )
        if  ( C [ i ][ j ] -  F [ i ][ j ])
            d [ i ] <?=  d [ j ];
    d [ i ]++;
}
 
int  preflow_push_relabel ( int  s ,  int  t )
{
    memset ( F ,  0 ,  sizeof ( F ));
    memset ( d ,  0 ,  sizeof ( d ));
    memset ( e ,  0 ,  sizeof ( e ));
    qf  =  qb  =  q ;
    d [ s ] =  N  -  1 ;    //设定源点高度，避免水太早灌回源点。
    preflow ( s ,  t );
 
    while  ( qf  <  qb )  //除源点汇点外还有含水点就继续
    {
        int  i  = * qf ++;
        relabel ( i );  //不一定能成功抬高此点，但无妨。
 
        for  ( int  j = 0 ;  j < 10 ; ++ j )
            if  ( d [ i ] ==  d [ j ] +  1  &&  C [ i ][ j ] -  F [ i ][ j ])
            {
                if  (! e [ j ] &&  j != s  &&  j != t ) * qb ++ =  j ;
                push ( i ,  j );
                if  (! e [ i ])  break ;
            }
 
        if  ( e [ i ]) * qb ++ =  i ;
    }
    return  e [ t ];
}