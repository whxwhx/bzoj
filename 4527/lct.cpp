namespace LCT{
	struct node *null;
	struct node{
		node *ch[2], *f;
		int s; bool rev;
		bool c() { return f == null || (f->ch[0] != this && f->ch[1] != this); }
		void st(node *o, int d) { (ch[d] = o)->f = this; }
		void upd() { s = ch[0]->s + ch[1]->s + 1; }
		void push() { if (rev) { rev = 0; swap(ch[0], ch[1]); ch[0]->rev ^= 1; ch[1]->rev ^= 1; }}
	}T[N];
	void rot(node *o){
		node *f = o->f; int d = o->d(); if (f->c()) o->f = f->f; else f->f->st(o, f->d());
		f->st(o->ch[d^1], d), o->st(f, d^1), f->upd();
	}
	void fix(node *o){ if (!o->c()) fix(o->f); o->push(); }
	void splay(node *o){
		fix(o);
		while (!o->c()) { if (!o->f->c()) (o->d() == o->f->d() ? rot(o->f) : rot(o)); rot(o); }
		upd(o);
	}
	void access(node *o){
		node *t = o;
		for(node *c = null; o != null; o = o->f) { splay(o); o->ch[1] = c; (c = o)->upd(); }
		splay(t);
	}
	void mroot(node *o){ access(o); o->rev ^= 1; }
	node *frt(node *o)
	{ access(o); for(o->push(); o->ch[1] != null; o = o->ch[1], o->push()); splay(o); return o;}
}