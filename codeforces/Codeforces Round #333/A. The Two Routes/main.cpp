/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年11月30日 星期一 16时10分45秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int max_n=400;

vector<int>ms[max_n+2];

struct node{
    int index;
    int len;

    node():index(0),len(0){}
    node(int index,int len):index(index),len(len){}

    bool operator<(const node& t)const
    {
        return len>t.len;
    }
};

priority_queue<node>pqueue;
bool visited[max_n+2];
int len[max_n+2];

int dj(int source,int n)
{
    for(int i=1;i<=n;++i)len[i]=1e9;

    pqueue.push(node(source,0));

    for(int i=0;i<n;++i)
    {    
        if(pqueue.empty())break;
        node nd;
        while(!pqueue.empty())
        {
            nd=pqueue.top();pqueue.pop();
            if(!visited[nd.index])
            {
                break;
            }
        }

        int index=nd.index;
        len[index]=nd.len;
        visited[index]=true;

        //cout<<"index:"<<index<<" len:"<<nd.len<<endl;

        if(index==n)
        {
            return len[index];
        }

        for(int i=0;i<ms[index].size();++i)
        {
            //cout<<"size:"<<ms[index].size()<<endl;
            int next=ms[index][i];
            if(!visited[next]&&len[index]+1<len[next])
            {
                len[next]=len[index]+1;
                pqueue.push(node(next,len[index]+1));
            }
        }
    }

    return -1;

}

int main()
{
    int n,m;
    cin>>n>>m;
    
    if(n==2)
    {
        cout<<-1<<endl;
        return 0;
    }

    int mp[max_n+2][max_n+2];
    memset(mp,0,sizeof(mp));

    do{
        int a,b;
        for(int i=0;i<m;++i)
        {
            cin>>a>>b;
            mp[a][b]=1;
            mp[b][a]=1;
        }
    }while(false);

    int flag=1-(mp[1][n]||mp[n][1]);
    //cout<<"flag:"<<flag<<endl;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(mp[i][j]==flag)
            {
                ms[i].push_back(j);
            }    
        }
    }

    cout<<dj(1,n)<<endl;
}
