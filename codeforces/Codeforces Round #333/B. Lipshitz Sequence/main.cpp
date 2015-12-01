/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月01日 星期二 14时51分45秒
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
#include<functional>
using namespace std;

const int max_n=100010;
int a[max_n];
int D[max_n];
int left_index[max_n];
int right_index[max_n];

void solve(int l,int r)
{
    if(l>r)swap(l,r);

    if(r-l<1)
    {
        cout<<0<<endl;
        return;
    }

    long long int ans=0;
    for(int i=l;i<r;++i)
    {
        ans+=(((long long(i-max(l-1,left_index[i]))*(min(r,right_index[i])-i))*D[i]);
    }
    cout<<ans<<endl;
}

struct point
{
    int m;
    int id;

    point(){}
    point(int m,int id):m(m),id(id){}
};
bool comp(const point&p1,const point&p2){
    if(p1.m==p2.m)
    {
        return p1.id<p2.id;
    }else{
        return p1.m<p2.m;
    }
}

int main()
{
    int n,q;
    cin>>n>>q;

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
    }

    point copy_D[max_n];
    for(int i=1;i<n;++i)
    {
        D[i-1]=abs(a[i]-a[i+1]);
        copy_D[i-1]=point(D[i-1],i-1);
    }

    //cout<<"D:";
    //for(int i=0;i<n-1;++i)
    //{
    //    cout<<D[i]<<" ";
    //}
    //cout<<endl;

    sort(copy_D,copy_D+n-1,comp);
    set<int,less<int> >setu;
    set<int,greater<int> >setl;

    //cout<<"copy_D"<<endl;
    //cout<<"m\tid"<<endl;
    //for(int i=0;i<n-1;++i)
    //{
    //    cout<<copy_D[i].m<<"\t"<<copy_D[i].id<<endl;
    //}

    for(int i=n-2;i>=0;--i)
    {
        set<int,less<int> >::iterator itu=setu.upper_bound(copy_D[i].id);
        if(itu==setu.end())
        {
            right_index[copy_D[i].id]=n-1;
        }else{
            right_index[copy_D[i].id]=*itu;
        }
        set<int,greater<int> >::iterator itl=setl.lower_bound(copy_D[i].id);
        if(itl==setl.end())
        {
            left_index[copy_D[i].id]=-1;
        }else{
            left_index[copy_D[i].id]=*itl;
        }
        setu.insert(copy_D[i].id);
        setl.insert(copy_D[i].id);
    }

    //cout<<"left:";
    //for(int i=0;i<n-1;++i)
    //{
    //    cout<<left_index[i]<<" ";
    //}
    //cout<<endl;

    //cout<<"right:";
    //for(int i=0;i<n-1;++i)
    //{
    //    cout<<right_index[i]<<" ";
    //}
    //cout<<endl;

    for(int i=0;i<q;++i)
    {
        int l,r;
        cin>>l>>r;
        solve(l-1,r-1);
    }
}
