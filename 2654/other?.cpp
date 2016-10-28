#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct ed{int x,y,z,color;}e[100010];
struct bian{int x,y,z,mrk;}a[100010];
inline bool operator<(const bian &a,const bian &b){return a.z<b.z||a.z==b.z&&a.mrk>b.mrk;}
int n,m,k,ans,tot,sum,tt;
int fa[100010];
inline int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
inline void jud(int mid)
{
    tot=sum=0;
    for (int i=1;i<=n;i++)fa[i]=i;
    for (int i=1;i<=m;i++)
    {
        a[i].x=e[i].x;
        a[i].y=e[i].y;
        a[i].z=e[i].z+(e[i].color*mid);
        a[i].mrk=e[i].color;
    }
    sort(a+1,a+m+1);
    for (int i=1;i<=m;i++)
    {
        int fx=getfa(a[i].x),fy=getfa(a[i].y);
        if (fx==fy)continue;
        if (a[i].mrk)tot++;
        fa[fx]=fy;
        sum+=a[i].z;
    }
}
int main()
{
    n=read();m=read();k=read();
    for (int i=1;i<=m;i++)
    {
        e[i].x=read()+1;
        e[i].y=read()+1;
        e[i].z=read();
        e[i].color=read()^1;
        if (e[i].color)tt++;
    }
    int l=-105,r=105;
    while (l<=r)
    {
        int mid=(l+r)>>1;
        jud(mid);
        cout <<mid<<' '<<tot<<endl;
        if (tot>=k){ans=sum-k*mid;l=mid+1;}
        else r=mid-1;
    }
    printf("%d\n",ans);
    return 0;
}