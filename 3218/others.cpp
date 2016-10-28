#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<map>
using namespace std;
   
#define INF 0x3f3f3f3f
   
#define N 5010
int a[N],b[N],w[N],l[N],r[N],p[N];
   
int seq[N*3],id;
   
struct MaxflowSolver{
    int head[300010],next[1000010],end[1000010],flow[1000010],ind;
    int d[300010],gap[300010],cur[300010],stk[300010],top;
    inline void reset(){ind=top=0,memset(head,-1,sizeof head);}
    inline void addedge(int a,int b,int f){int q=ind++;end[q]=b,next[q]=head[a],head[a]=q,flow[q]=f;}
    inline void make(int a,int b,int f){/*printf("%d %d %d\n",a,b,f);*/addedge(a,b,f),addedge(b,a,0);}
    inline void bfs(int T){
        static int q[300010];int fr=0,ta=0;
        memset(d,-1,sizeof d),memset(gap,0,sizeof gap),++gap[d[T]=0],q[ta++]=T;
        while(fr^ta){
            int i=q[fr++];for(int j=head[i];j!=-1;j=next[j])if(d[end[j]]==-1)++gap[d[end[j]]=d[i]+1],q[ta++]=end[j];
        }
    }
    inline int Maxflow(int S,int T,int cnt){
        int res=0,i,Min,ins,u=S;bfs(T),memcpy(cur,head,sizeof cur);
        while(d[S]<cnt){
            if(u==T){
                for(Min=INF,i=0;i<top;++i)if(Min>flow[stk[i]])Min=flow[stk[i]],ins=i;
                for(res+=Min,i=0;i<top;++i)flow[stk[i]]-=Min,flow[stk[i]^1]+=Min;
                u=end[stk[top=ins]^1];
            }
            if(u!=T&&!gap[d[u]-1])break;
            bool find=0;
            for(int&j=cur[u];j!=-1;j=next[j])if(flow[j]&&d[u]==d[end[j]]+1){find=1,ins=j;break;}
            if(find){cur[u]=stk[top++]=ins,u=end[ins];}
            else{
                Min=cnt;for(int j=head[u];j!=-1;j=next[j])if(flow[j]&&d[end[j]]<Min)Min=d[end[j]],cur[u]=j;
                if(!--gap[d[u]])break;++gap[d[u]=Min+1];
                if(u!=S)u=end[stk[--top]^1];
            }
        }return res;
    }
}SteinsGate;
   
struct Node{
    int l,r;
}S[300010];int cnt;
   
int root[5010];
int Newversion(int last,int tl,int tr,int ins){
    int q=++cnt;S[q]=S[last];if(last)SteinsGate.make(last,q,INF);if(tl==tr)return q;
    int mid=(tl+tr)>>1;
    if(ins<=mid)S[q].l=Newversion(S[last].l,tl,mid,ins);else S[q].r=Newversion(S[last].r,mid+1,tr,ins);
    return q;
}
   
void Addedge(int q,int tl,int tr,int dl,int dr,int topoint){
    if(dl<=tl&&tr<=dr){if(q)SteinsGate.make(q,topoint,INF);return;}
    int mid=(tl+tr)>>1;
    if(dr<=mid)Addedge(S[q].l,tl,mid,dl,dr,topoint);
    else if(dl>mid)Addedge(S[q].r,mid+1,tr,dl,dr,topoint);
    else Addedge(S[q].l,tl,mid,dl,mid,topoint),Addedge(S[q].r,mid+1,tr,mid+1,dr,topoint);
}
   
int main(){
    int n;scanf("%d",&n);register int i,j;
    for(i=1;i<=n;++i)scanf("%d%d%d%d%d%d",&a[i],&b[i],&w[i],&l[i],&r[i],&p[i]);
   
    for(i=1;i<=n;++i)seq[++id]=a[i],seq[++id]=l[i],seq[++id]=r[i];sort(seq+1,seq+id+1);
    map<int,int>M;int num=0;
    for(seq[0]=-1<<30,i=1;i<=id;++i)if(seq[i]!=seq[i-1])M[seq[i]]=++num;
    for(i=1;i<=n;++i)a[i]=M[a[i]],l[i]=M[l[i]],r[i]=M[r[i]];
   
    SteinsGate.reset();
    for(i=1;i<=n;++i)root[i]=Newversion(root[i-1],1,num,a[i]),SteinsGate.make(250000+i,cnt,INF);
    for(i=1;i<=cnt;++i){
        if(S[i].l)SteinsGate.make(S[i].l,i,INF);
        if(S[i].r)SteinsGate.make(S[i].r,i,INF);
    }
   
    int S=0,T=++cnt,res=0;
    for(i=1;i<=n;++i)res+=b[i]+w[i],SteinsGate.make(S,250000+i,w[i]),SteinsGate.make(250000+i,T,b[i]);
    for(i=1;i<=n;++i)if(i)Addedge(root[i-1],1,num,l[i],r[i],++cnt),SteinsGate.make(cnt,250000+i,p[i]);
   
    printf("%d",res-SteinsGate.Maxflow(S,T,cnt+1+n));
   
#ifndef ONLINE_JUDGE
    system("pause");
#endif
   
    return 0;
}