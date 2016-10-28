struct node{
	node *next[26], *f;
	int cnt, len, num;
}T[N];
int tl = 0;
node *nn(){return &T[++tl];}
node *p, r0, rm1;
void init(){
	r0 = nn(), rm1 = nn();
	r0 -> f = rm1;
	r0 -> len = 0, rm1 -> len = -1;
	p = rm1;
}
void add(int x, int l){
	node *w = p;
	for(;s[l - w->len - 1] - 'a' != x; w = w->f);
	if (w->next[x]) p = w->next[x];
	else {
		p = nn(), p->len = w->len + 2;
		node *q = w->f;
		if (!q) p = r0;
		else{
			for(;s[l - q->len - 1] - 'a' != x; q = q->f);
			p->f = q->next[x];
		}
		w->next[x] = p;
		p->num = p->f->num + 1;
	}
	p->cnt++;
}