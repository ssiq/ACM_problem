void merge(int v[],int begin,int mid,int end)
{
    int a1=begin,b1=mid;
    int a2=mid+1,b2=end;

    tn=0;

    while(a1<=b1||a2<=b2)
    {
        if(a1>b1)
        {
            temp[tn++]=v[a2];
            ++a2;
        }else if(a2>b2){
            temp[tn++]=v[a1];
            ++a1;
        }else{
            if(v[a1]<=v[a2])
            {
                temp[tn++]=v[a1];
                ++a1;
            }else{
                temp[tn++]=v[a2];
                ++a2;
            }
        }
    }
}

void sort(int v[],int begin,int end,long long int& num)
{
    if(begin>=end)
    {
        return;
    }

    int mid=((begin+end)>>1);
    sort(v,begin,mid,num);
    sort(v,mid+1,end,num);
    merge(v,begin,mid,end,num);
}