//这个计算组合数的方法需要模p是质数，同时invfac(a)的a不能是p的倍数
//一般情况下计数问题都是通过动态规划来计算的，但也有些情况下会受制于内存的限制无法缓存下所有的动态年规划的状态，或者动态规划的递归公式非常复杂而组合公式非常显然，这是候就可以直接使用组合数公式计算
const int p=1000000007;//这里的p就是一个质数

int Power(int a,int b)//这是一个快速计算幂的函数
{
	int ans=1;
	for(;b;b>>=1)
	{
		if(b&1)ans=(long long)ans*a%p;
		a=(long long)a*a%p;
	}
	return ans;
}

fac[0]=1;
for(i=1;i<=n;++i)fac[i]=(long long)fac[i-1]*i%p;
for(i=0;i<=n;++i)fac_inv[i]=Power(fac[i],p-2);
