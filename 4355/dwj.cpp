#include <cstdio>
#include <cctype>
#define repu(i,x,y) for (int i=x; i<=y; ++i)
#define mid (l+r>>1)
#define lc x<<1
#define rc x<<1|1
using namespace std;

typedef long long LL;
int n,m,type,ql,qr,w,cnt[1048576],tag2[1048576],ans;
LL min1[1048576],min2[1048576],tag1[1048576];
char ch;

inline int getint()
{
    while (!isdigit(ch=getchar()) && ch!='-');
    bool flag=ch=='-';
    if (flag)
        ch=getchar();
    int x=ch-'0';
    for (; isdigit(ch=getchar()); x=x*10+ch-'0');
    return flag?-x:x;
}

void update(int x)
{
    min1[x]=min1[lc],min2[x]=min2[lc],cnt[x]=cnt[lc];
    if (min1[rc]<min1[x])
        min2[x]=min1[x],min1[x]=min1[rc],cnt[x]=cnt[rc];
    else
        if (min1[rc]==min1[x])
            cnt[x]+=cnt[rc];
        else
            if (min1[rc]<min2[x])
                min2[x]=min1[rc];
    if (min2[rc]<min2[x])
        min2[x]=min1[rc];
}

void cover(int x,int w,int len)
{
    tag1[x]=0,tag2[x]=min1[x]=w,min2[x]=1LL<<60,cnt[x]=len;
}

void push_down(int x,int l,int r);

void max(int x,int w,int l,int r)
{
    min1[x]+=w,min2[x]+=w,tag1[x]+=w;
    if (min1[x]>=0)
        return;
    if (min2[x]+w>0)
    {
        min1[x]=0;
        return;
    }
    push_down(x,l,r),update(x);
}

void push_down(int x,int l,int r)
{
    if (tag1[x])
        max(lc,tag1[x],l,mid),max(rc,tag1[x],mid+1,r),tag1[x]=0;
    if (tag2[x]!=-1)
        cover(lc,tag2[x],mid-l+1),cover(rc,tag2[x],r-mid),tag2[x]=-1;
}

void build(int x,int l,int r)
{
    if (l==r)
    {
        cover(x,getint(),1);
        return;
    }
    build(lc,l,mid),build(rc,mid+1,r),update(x),tag2[x]=-1;
}

void work(int x,int l,int r)
{
    if (ql<=l && qr>=r)
    {
        if (type==1)
            cover(x,w,r-l+1);
        if (type==2)
            max(x,w,l,r);
        if (type==3)
            ans+=cnt[x]*(!min1[x]);
        return;
    }
    push_down(x,l,r);
    if (ql<=mid)
        work(lc,l,mid);
    if (qr>mid)
        work(rc,mid+1,r);
    if (type<3)
        update(x);
}

int main(){
    scanf("%d%d",&n,&m);
    build(1,1,n);
    while (m--)
    {
        type=getint(),ql=getint(),qr=getint();
        if (type<=2)
            w=getint();
        else
            ans=0;
        work(1,1,n);
        if (type==3)
            printf("%d\n",ans);
    }
    return 0;
}