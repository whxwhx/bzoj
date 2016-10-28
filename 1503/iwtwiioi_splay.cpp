#include <cstdio>
using namespace std;
 
class Splay {
public:
    struct node {
        node* ch[2], *fa;
        int key, size;
        node() { ch[0]=ch[1]=fa=0; key=size=0; }
        void pushup() { size=ch[0]->size+ch[1]->size+1; }
        bool d() { return fa->ch[1]==this; }
        void setc(node* c, bool d) { ch[d]=c; c->fa=this; }
    }*null, * root;
    Splay() {
        null=new node;
        null->ch[0]=null->ch[1]=null->fa=null;
        root=null;
    }
    void rot(node* rt) {
        node* fa=rt->fa; bool d=rt->d();
        fa->fa->setc(rt, fa->d());
        fa->setc(rt->ch[!d], d);
        rt->setc(fa, !d);
        fa->pushup();
        if(root==fa) root=rt;
    }
    node* newnode(const int &key) {
        node* ret=new node();
        ret->key=key; ret->size=1;
        ret->ch[0]=ret->ch[1]=ret->fa=null;
        return ret;
    }
    void splay(node* rt, node* fa) {
        while(rt->fa!=fa)
            if(rt->fa->fa==fa) rot(rt);
            else rt->d()==rt->fa->d()?(rot(rt->fa), rot(rt)):(rot(rt), rot(rt));
        rt->pushup();
    }
    void insert(const int &key) {
        if(root==null) { root=newnode(key); return; }
        node* t=root;
        while(t->ch[key>t->key]!=null) t=t->ch[key>t->key];
        node* c=newnode(key);
        t->setc(c, key>t->key);
        t->pushup();
        splay(c, null);
    }
    void remove(const int &key) {
        node* t=root;
        while(t!=null && t->key!=key) t=t->ch[key>t->key];
        if(t==null) return;
        splay(t, null);
        node* rt=root->ch[0];
        if(rt==null) rt=root->ch[1];
        else {
            node* m=rt->ch[1];
            while(m!=null && m->ch[1]!=null) m=m->ch[1];
            if(m!=null) splay(m, root);
            rt=root->ch[0];
            rt->setc(root->ch[1], 1);
        }
        delete root;
        root=rt;
        root->fa=null;
        if(root!=null) root->pushup();
    }
    int rank(const int &key, node* rt) {
        if(rt==null) return 0;
        int s=rt->ch[0]->size+1;
        if(key==rt->key) return s;
        if(key>rt->key) return s+rank(key, rt->ch[1]);
        else return rank(key, rt->ch[0]);
    }
    node* select(const int &k, node* rt) {
        if(rt==null) return null;
        int s=rt->ch[0]->size+1;
        if(s==k) return rt;
        if(k>s) return select(k-s, rt->ch[1]);
        else return select(k, rt->ch[0]);
    }
};
 
int main() {
    int n, m, ans=0, t, m1=0;
    Splay tree;
    scanf("%d%d", &n, &m);
    char str[3];
    while(n--) {
        scanf("%s%d", str, &t);
        if(str[0]=='I') {
            if(t<m) continue;
            tree.insert(t+m1);
        }
        else if(str[0]=='F') {
            if(t>tree.root->size) printf("-1\n");
            else {
                printf("%d\n", tree.select(tree.root->size-t+1, tree.root)->key-m1);
            }
        }
        else if(str[0]=='S') {
            m1+=t;
            tree.insert(m+m1);
            ans+=tree.root->ch[0]->size;
            tree.root=tree.root->ch[1];
            tree.root->fa=tree.null;
        }
        else if(str[0]=='A') {
            m1-=t;
        }
    }
    printf("%d\n", ans);
    return 0;
}