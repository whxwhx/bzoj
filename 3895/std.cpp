#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 1010
using namespace std;
char f[60][50500];
//1-先手必胜 0-先手必败
int n;
char Memorial_Search(int a,int b)
{
    if(a==0) return b&1;
    //当不存在大小为1的堆时按照操作数计算必胜或必败
    if(b==1) return Memorial_Search(a+1,0);
    //若操作数为1则此时b部分只有1个石子 划到a中
    if(~f[a][b]) return f[a][b];
    char &re=f[a][b];
    if( a && !Memorial_Search(a-1,b) )
        return re=true;
    //取走某个大小为1的堆中的石子
    if( a && b && !Memorial_Search(a-1,b+1) )
        return re=true;
    //将某个大小为1的堆中的石子与某个大小不为1的堆合并
    if( a>=2 && !Memorial_Search(a-2,b+2+(b?1:0) ) )
        return re=true;
    //将两个大小为1的堆中石子合并
    if( b && !Memorial_Search(a,b-1) )
        return re=true;
    //对大小>1的堆进行合并或取走石子使操作数-1
    return re=false;
}
int main()
{
    int T,i,x;
    memset(f,-1,sizeof f);
    for(cin>>T;T;T--)
    {
        cin>>n;
        int a=0,b=-1;
        for(i=1;i<=n;i++)
        {
            scanf("%d",&x);
            if(x==1) ++a;
            else b+=x+1;
        }
        if(b==-1) b=0;
        puts(Memorial_Search(a,b)?"YES":"NO");
    }
    return 0;
}
