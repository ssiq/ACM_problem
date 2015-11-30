int mp[size][size]
int dist[size][size]

for(int i=0;i<size;++i)
{
    for(int j=0;j<size;++j)
    {
    	dist[i][j]=mp[i][j];
    }
}

for(int k=0;k<size;++k)
{
	for(int i=0;i<size;++i)
	{
		for(int j=0;j<size;++j)
		{
			dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
		}
	}
}

//find the min cycle with this algorithm
int answer=MAX_INT;
for(int k=0;k<size;++k)
{
	for(int i=0;i<k-1;++i)
	{
		for(int j=0;j<k-1;++j)
		{
			answer=min(answer,dist[i][j]+dist[i][k]+dist[k][j]);
		}
	}

	for(int i=0;i<size;++i)
	{
		for(int j=0;j<size;++j)
		{
			dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
		}
	}
}