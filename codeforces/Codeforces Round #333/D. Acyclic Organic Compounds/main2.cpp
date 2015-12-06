/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月03日 星期四 13时15分06秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

const int letter_num=26;

struct Node{
    bool isword;
    int size;
    Node* next[letter_num];
};

const int max_n=300100;
int c[max_n];
char letter[max_n];
int n;
vector<int>mp[max_n];
Node v_nodes[max_n];
Node node_pool[1000000];

Node* get_next()
{
    static int node_index=0;
    return &node_pool[node_index++];
}

int max_diff;
int max_diff_num;

void union_trie(Node* from,Node* to)
{
    for(int i=0;i<letter_num;++i)
    {
        if(from->next[i]!=0)
        {
            if(to->next[i]==0)
            {
                to->next[i]=from->next[i];
            }else{
                union_trie(from->next[i],to->next[i]);
            }
        }
    }

    int size=0;
    for(int i=0;i<letter_num;++i)
    {
        if(to->next[i]!=0)
        {
            size+=to->next[i]->size+1;
        }
    }
    to->size=size;
}

void dfs(int index,int up)
{
    for(int i=0;i<mp[index].size();++i)
    {
        int next=mp[index][i];
        if(next==up)continue;
        dfs(next,index);
    }

    auto node_ptr=get_next();
    for(int i=0;i<mp[index].size();++i)
    {
        int next=mp[index][i];
        if(next==up)continue;
        union_trie(&v_nodes[next],node_ptr);
    }

    v_nodes[index].next[letter[index]-'a']=node_ptr;
    v_nodes[index].size=node_ptr->size+1;
    
    int diff=node_ptr->size+c[index]+1;
    if(diff>max_diff)
    {
        max_diff=diff;
        max_diff_num=1;
    }else if(diff==max_diff){
        max_diff_num+=1;
    }
}

int main()
{
    cin>>n;
    do{
        for(int i=1;i<=n;++i)
        {
            cin>>c[i];    
        }

        for(int i=1;i<=n;++i)
        {
            cin>>letter[i];
        }

        int a,b;
        for(int i=0;i<n-1;++i)
        {
            cin>>a>>b;
            mp[a].push_back(b);
            mp[b].push_back(a);
        }
    }while(false);

    dfs(1,0);

    cout<<max_diff<<endl;
    cout<<max_diff_num<<endl;
}
