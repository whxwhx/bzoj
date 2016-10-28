#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1001000
#define T 26
using namespace std;
struct KSD
{
	int v,next;
}e[N];
int head[N],cnt;
inline void add(int u,int v)
{
	cnt++;
	e[cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
int size[N];

int pa[N],son[N][T],dep[N];
int tot=1,last=1;
inline int newnode(int _dep){dep[++tot]=_dep;return tot;}
inline void SAM(int alp)
{
	int p=newnode(dep[last]+1);
	size[p]=1;
	int u=last;
	while(u&&!son[u][alp])son[u][alp]=p,u=pa[u];
	if(!u)pa[p]=1;
	else {
		int v=son[u][alp];
		if(dep[v]==dep[u]+1)pa[p]=v;
		else {
			int nv=newnode(dep[u]+1);
			pa[nv]=pa[v],pa[v]=pa[p]=nv;
			memcpy(son[nv],son[v],sizeof son[nv]);
			while(u&&son[u][alp]==v)son[u][alp]=nv,u=pa[u];
		}
	}
	last=p;
}
long long ans;
void tree_dp(int x,int p)
{
	int i,v;
	for(i=head[x];i;i=e[i].next)
	{
		tree_dp(v=e[i].v,x);
		size[x]+=size[v];
	}
	dep[x]-=dep[p];
	ans-=(long long)size[x]*(size[x]-1)*dep[x];
}
char str[N];
int main()
{
//	freopen("test.in","r",stdin);
	int i,j,k;
	scanf("%s",str);
	int len=strlen(str);
	for(i=len-1;i>=0;i--)SAM(str[i]-'a');
	ans=(long long)(len-1)*len*(len+1)>>1;
	for(i=2;i<=tot;i++)add(pa[i],i);
	for(i=head[1];i;i=e[i].next)tree_dp(e[i].v,1);
	cout<<ans<<endl;
	return 0;
}