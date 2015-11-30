class find_max_flow{
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

	const static int max_N=210;
	edge epools[max_N*max_N];
	edge* get_next()
	{
		static int last=0;
		return &epools[++last];
	}
	vector<edge*>mp[max_N];
public:	
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

	void link(int c,int d,int cap)
	{
		DEBUG_OUT("link a:"<<c<<" d:"<<d<<" cap:"<<cap);
		edge *a=get_next(),*b=get_next();
		mp[c].push_back(a);
		a->set(c,d,cap,b);
		mp[d].push_back(b);
		b->set(d,c,0,a);
	}

};