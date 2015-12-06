/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月05日 星期六 13时42分29秒
 ************************************************************************/

#include<cstdio>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

//#define DEBUG

const int max_N=10010;
const int root=0;
const int LN=14;

int chainNo,chainInd[max_N],chainHead[max_N],posInBase[max_N],baseNode[max_N];
int subsize[max_N],depth[max_N];
vector<int>adj[max_N],costs[max_N],indexx[max_N];
int baseArray[max_N],ptr;
int pa[LN][max_N];
int otherEnd[max_N];

int LCA(int u, int v) {
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for(int i=0; i<LN; i++) if( (diff>>i)&1  ) u = pa[i][u];
    if(u == v) return u;
    for(int i=LN-1; i>=0; i--) if(pa[i][u] != pa[i][v]) {
        u = pa[i][u];
        v = pa[i][v];
    }
    return pa[0][u];
}

void dfs(int index,int pre,int _depth)
{
    depth[index]=_depth;
    int _subsize=1;
    for(int i=0;i<adj[index].size();++i)
    {
        int next=adj[index][i];
        if(next==pre)continue;
        otherEnd[indexx[index][i]]=adj[index][i];
        dfs(next,index,_depth+1);
        _subsize+=subsize[next];
    }
    pa[0][index]=pre;
    subsize[index]=_subsize;
}

void HLD(int curNode,int cost,int pre)
{
    if(chainHead[chainNo]==-1)
    {
        chainHead[chainNo]=curNode;
    }
    chainInd[curNode]=chainNo;
    posInBase[curNode]=ptr;
    baseNode[ptr]=curNode;
    baseArray[ptr++]=cost;

    int sc=-1,ncost,nsize;
    for(int i=0;i<adj[curNode].size();++i)
    {
        int next=adj[curNode][i];
        if(next==pre)continue;
        if(sc==-1||subsize[next]>nsize)
        {
            sc=next;
            nsize=subsize[next];
            ncost=costs[curNode][i];
        }
    }

    if(sc!=-1)
    {
        HLD(sc,ncost,curNode);
    }

    for(int i=0;i<adj[curNode].size();++i)
    {
        int next=adj[curNode][i];
        if(next==pre||next==sc)continue;
        chainNo++;
        HLD(next,costs[curNode][i],curNode);
    }
}


int prefix_array[max_N];
void make_prefix_array(int len)
{
    prefix_array[0]=baseArray[0];
    for(int i=1;i<len;++i)
    {
        prefix_array[i]=prefix_array[i-1]+baseArray[i];
    }
}

int query_up(int low,int up)
{
    if(chainInd[low]==chainInd[up])
    {
        return prefix_array[posInBase[low]]-prefix_array[posInBase[up]];
    }else{
        int head_low=chainHead[chainInd[low]];
        return prefix_array[posInBase[low]]-prefix_array[posInBase[head_low]]+baseArray[posInBase[head_low]]+query_up(pa[0][head_low],up);
    }
}

void find_len(int a,int b)
{
    if(chainInd[a]==chainInd[b])
    {
        if(depth[b]>depth[a])swap(a,b);
        printf("%d\n",query_up(a,b));
    }else{
        int ace=LCA(a,b);
        int l1=query_up(a,ace);
        int l2=query_up(b,ace);
        printf("%d\n",l1+l2);
    }
}

void query_up_kth(int low,int up,vector<pair<int,int> >& v,int base)
{
    v.push_back(make_pair(low,base+1));
    if(chainInd[low]==chainInd[up])
    {
        v.push_back(make_pair(up,base+posInBase[low]-posInBase[up]+1));
    }else{
        int head=chainHead[chainInd[low]];
        v.push_back(make_pair(head,base+posInBase[low]-posInBase[head]+1));
        query_up_kth(pa[0][head],up,v,v.back().second);
    }
}

int find_in_vec(int c,const vector<pair<int,int> >&v)
{

    for(int i=1;i<v.size();i+=2)
    {
        if(v[i].second>=c)
        {
#ifdef DEBUG
            printf("i: %d\n",i);
            printf("i-1 index:%d\n",posInBase[v[i-1].first]);
            printf("result index:%d\n",posInBase[v[i-1].first]+(c-v[i-1].second));
            printf("baseNode{5}, baseNode[6]:%d,%d\n",baseNode[5],baseNode[6]);
            printf("posInBase 5,2:%d,%d\n",posInBase[5],posInBase[2]);
#endif
            return baseNode[posInBase[v[i-1].first]-(c-v[i-1].second)];
        }
    }
}

int find_kth(int a,int b,int c)
{
    if(chainInd[a]==chainInd[b])
    {
        if(depth[b]>depth[a])
        {
            swap(a,b);
            c=(posInBase[a]-posInBase[b]+1)-c+1;
        }
        return baseNode[posInBase[a]-c+1];
    }else{
        int ace=LCA(a,b);
        int now_num=0;
//        int na=a,nb=b;
//        while(true)
//        {
//            int field_len=0;
//            if(chainInd[na]==chainInd[ace])
//            {
//                field_len=posInBase[na]-posInBase[ace]+1;
//            }else{
//                field_len=posInBase[na]-posInBase[chainHead[chainInd[na]]]; 
//            }
//            if(now_num+field_len>k)
//            {
//                return baseNode[posInBase[na]+k-now_num-1];
//            }else{
//                now_num+=field_len;
//            }
//            if(chainInd[na]==chainInd[ace])break;
//            na=pa[0][chainHead[chainInd[na]]];
//        }
        vector<pair<int,int> >va,vb;
        query_up_kth(a,ace,va,0);
        query_up_kth(b,ace,vb,0);

#ifdef DEBUG
        printf("%d\n",va.back().second);
#endif

        if(va.back().second>c)
        {
            return find_in_vec(c,va);
        }else if(va.back().second==c){
            return ace;
        }else{
            c=vb.back().second-(c-va.back().second+1)+1;
#ifdef DEBUG
            for(int i=0;i<vb.size();++i)
            {
                printf("%d %d\n",vb[i].first,vb[i].second);
            }
            printf("new c:%d\n",c);
#endif            
            return find_in_vec(c,vb);
        }
    }
}

void solve()
{
    int N;
    scanf("%d",&N);

    ptr=0;
    chainNo=0;
    for(int i=0;i<N;++i)
    {
        chainHead[i]=-1;
        adj[i].clear();
        costs[i].clear();
        indexx[i].clear();
        for(int j=0;j<LN;++j)pa[j][i]=-1;
    }

    for(int i=0;i<N-1;++i)
    {
        int u,v,c;
        scanf("%d %d %d",&u,&v,&c);
        adj[u-1].push_back(v-1);
        costs[u-1].push_back(c);
        indexx[u-1].push_back(i);
        adj[v-1].push_back(u-1);
        costs[v-1].push_back(c);
        indexx[v-1].push_back(i);
    }

    dfs(root,-1,0);
    HLD(root,-1,-1);
    make_prefix_array(ptr);

    // Below Dynamic programming code is for LCA.
    for(int i=1; i<LN; i++)
        for(int j=0; j<N; j++)
            if(pa[i-1][j] != -1)
                pa[i][j] = pa[i-1][pa[i-1][j]];

    char s[100];
    while(true)
    {
        scanf("%s",s);
        if(s[0]=='D')
        {
            if(s[1]=='O')
            {
                break;
            }
        }

        if(s[0]=='K')
        {
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            printf("%d\n",find_kth(a-1,b-1,c)+1);
        }else{
            int a,b;
            scanf("%d %d",&a,&b);
            find_len(a-1,b-1);
        }
    }
}

int main()
{
    int t;
    scanf("%d",&t);

    for(int i=0;i<t;++i)
    {
        solve();
    }
}
