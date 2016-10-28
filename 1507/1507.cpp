#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
const int N = 1024 * 1024 * 2;
using namespace std;
struct node{
    node *l, *r;
    int s;
    char v;
}T[N];
int l = 0;
node *nn(){
    l++;
    T[l].l = T[l].r = NULL;
    T[l].s = 1;
    return &T[l];
}
#define sz(a) (a ? a->s : 0)
void upd(node *a){
    a->s = sz(a->l) + sz(a->r) + 1;
}
node *merge(node *a, node *b){
    if (!a) return b; else if (!b) return a;
    if (rand() % (a->s + b->s) < (a->s)) {
        a->r = merge(a->r, b), upd(a);
        return a;
    }else{
        b->l = merge(a, b->l), upd(b);
        return b;
    }
}
typedef pair<node*, node*> np;
#define mp(a,b) make_pair(a,b)
np split(node *a, int n){
    if (!a) return mp((node*)NULL,(node*)NULL);
    pair<node*, node*> t;
    int cnt = sz(a->l);
    if (cnt >= n){
        t = split(a->l, n);
        a->l = t.second, upd(a);
        return mp(t.first, a);
    }else{
        t = split(a->r, n - cnt - 1);
        a->r = t.first, upd(a);
        return mp(a, t.second);
    }
}
void print(node *a){
    if (!a) return;
    print(a->l);
    printf("%c",a->v);
    print(a->r);
}
char op[30];
node* root;
int main(){
    srand(233);
    int t; scanf("%d",&t);
    int index = 0;
    rep(i,1,t){
        scanf("%s",op);
        if (op[0] == 'M'){
            int k; scanf("%d",&k);
            index = k;
        }else if (op[0] == 'I'){
            int n; scanf("%d",&n);
            np a1 = split(root, index);
            rep(i,1,n){
                node *t1 = nn();
                char c = getchar();
                while (c < 32 || c > 126) c = getchar();
                t1->v = c;
                a1.first = merge(a1.first, t1);
            }
            root = merge(a1.first, a1.second);
        }else if (op[0] == 'D'){
            int n; scanf("%d",&n);
            np a1 = split(root, index);
            np a2 = split(a1.second, n);
            root = merge(a1.first, a2.second);                      
        }else if (op[0] == 'G'){
            int n; scanf("%d",&n);
            np a1 = split(root, index);
            np a2 = split(a1.second, n);
            print(a2.first), printf("\n");
            a1.second = merge(a2.first, a2.second);
            root = merge(a1.first, a1.second);
        }else if (op[0] == 'P') index--;
        else  if (op[0] == 'N') index++;
    }
    return 0;
}