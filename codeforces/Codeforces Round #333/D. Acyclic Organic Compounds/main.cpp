/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月03日 星期四 13时15分06秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>
#include<algorithm>
using namespace std;

//struct Node{
//    Node* left;
//    Node* right;
//    char c;
//};

const int max_n=300100;
int c[max_n];
char letter[max_n];
int n;
vector<int>mp[max_n];
unordered_set<string>v_set[max_n];

int max_diff;
int max_diff_num;

void dfs(int index,int up)
{
    for(int i=0;i<mp[index].size();++i)
    {
        int next=mp[index][i];
        if(next==up)continue;
        dfs(next,index);
    }

    auto* setptr=&v_set[index];
    auto s=string(1,letter[index]);
    setptr->rehash(100);
    setptr->max_load_factor(0.7);
    setptr->insert(s);
    for(int i=0;i<mp[index].size();++i)
    {
        int next=mp[index][i];
        if(next==up)continue;
        for(auto p=v_set[next].begin();p!=v_set[next].end();++p)
        {
            setptr->insert(s+*p);
        }
    }

    int diff=setptr->size()+c[index];
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
