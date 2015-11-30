void create_next_array(string s,vector<int>& n)
{
	n[0]=0;
	for(int i=1;i<s.size();++i)
	{
		int j=n[i-1];
		while(j!=0&&s[i]!=s[j]){j=n[j-1];}
		if(s[i]==s[j])
		{
			n[i]=j+1;
		}else{
			n[i]=0;
		}
	}
}