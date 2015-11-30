template<typename T>
class fast_power_algorithm
{
public:
	T solve(T to_pow,int power_number,T e)
	{
		const int max_pow=32;
		T p[max_pow];
		p[0]=to_pow;
		for(int i=1;i<max_pow;++i)
		{
			p[i]=p[i-1]*p[i-1];
		}

		T r=e;
		for(int i=0;i<max_pow;++i)
		{
			if(((power_number>>i)&1)==1)
			{
				r=r*p[i];
			}
		}

		return r;
	}
};