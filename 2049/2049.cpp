#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20000;
struct node *null;
char ss[100];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    null=&s[0];null->ch[0]=null->ch[1]=null->f=null;null->rev=0;
    rep(i,1,n) {
        s[i].ch[0]=s[i].ch[1]=s[i].f=null;
        s[i].rev=0;
    }
    rep(i,1,m){
        int a,b;scanf("%s%d%d",ss,&a,&b);
        char c=ss[0];
        if (c=='Q') printf(frt(&s[a])==frt(&s[b])?"Yes\n" : "No\n");
        else if (c=='C') link(&s[a],&s[b]);
        else if (c=='D') {
            mrt(&s[a]);
            cut(&s[b]);
        }
    }
    return 0;
}