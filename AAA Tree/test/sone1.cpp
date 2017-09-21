#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <functional>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
const int INF = 1e8;
namespace sjtu {
template <class T>
class AAA_tree
{
private:
	struct AAA_Node;
	struct Splay;
	struct Splay_Node;
	
	struct AAA_Node
	{
		AAA_tree *ptr;
		AAA_Node* son[2], *fa;
		Splay light_sons;
		bool rev;
		int id, size_path, size_subtree;
		T val;
		T data_path, data_subtree;
		T tag_path, tag_subtree;
		int tag_path_type, tag_subtree_type;//0:no tag;	1:cover_tag;	2:add_tag
		AAA_Node(AAA_tree *other_ptr, int id):id(id), size_path(1), size_subtree(0), ptr(other_ptr), fa(NULL), rev(0), tag_path_type(0), tag_subtree_type(0)
		{
			son[0] = son[1] = NULL;
		}
		int size()
		{
			return size_path + size_subtree;
		}
		T data() const
		{
			return data_path + data_subtree;
		}
		void change_path(T delt, int type)//1:cover_tag;	2:add_tag
		{
			if(type == 1)
			{
				data_path = size_path * delt;
				val = delt;
				tag_path = delt;
				tag_path_type = 1;
			}else//type == 2
			{
				if(tag_path_type == 0)
				{
					data_path = data_path & (size_path * delt);
					tag_path = delt;
					val = val & delt;
					tag_path_type = 2;
				}else
				{
					data_path = data_path & (size_path * delt);
					val = val & delt;
					tag_path = tag_path & delt;
				}
			}
		}
		void update_path()
		{
			data_path = val;
			if(son[0]) data_path = data_path + son[0] -> data_path;
			if(son[1]) data_path = data_path + son[1] -> data_path;
		}
		void change_subtree(T delt, int type)//1:cover_tag;	2:add_tag
		{
			if(type == 1)
			{
				if(size_subtree) data_subtree = size_subtree * delt;
				tag_subtree = delt;
				tag_subtree_type = 1;
			}else//type == 2
			{
				if(tag_subtree_type == 0)
				{
					if(size_subtree) data_subtree = data_subtree & (size_subtree * delt);
					tag_subtree = delt;
					tag_subtree_type = 2;
				}else
				{
					if(size_subtree) data_subtree = data_subtree & (size_subtree * delt);
					tag_subtree = tag_subtree & delt;
				}
			}
		}
		void change_all(T delt, int type)//1:cover_tag;	2:add_tag
		{
			change_path(delt, type);
			change_subtree(delt, type);
		}
		
		void downtag_rev()
		{
			std::swap(son[0],son[1]);
			rev ^= 1;
		}
		void downtag_path()
		{
			if(tag_path_type == 0)return;
			if(son[0]) son[0] -> change_path(tag_path, tag_path_type);
			if(son[1]) son[1] -> change_path(tag_path, tag_path_type);
			tag_path_type = 0;
		}
		void downtag_subtree()
		{
			if(tag_subtree_type == 0)return;
			if(light_sons.size) (light_sons.root) -> change(tag_subtree, tag_subtree_type);
			if(son[0]) son[0]->change_subtree(tag_subtree, tag_subtree_type);
			if(son[1]) son[1]->change_subtree(tag_subtree, tag_subtree_type);
			tag_subtree_type = 0;
		}
		void push_down()
		{
			if (rev)
			{
				if (son[0]) son[0] -> downtag_rev();
				if (son[1]) son[1] -> downtag_rev();
				rev = 0;
			}
			downtag_path();
			downtag_subtree();
		}
		void update()
		{
			data_path = val;
			size_path = 1;
			//if(lightsize_subtree = light_sons.root -> size;
			if(son[0]) 
			{
				data_path = data_path + son[0] -> data_path;
				size_path += son[0] -> size_path;
				size_subtree += son[0] -> size_subtree;
			}
			if(son[1]) 
			{
				data_path = data_path + son[1] -> data_path;
				size_path += son[1] -> size_path;
				size_subtree += son[1] -> size_subtree;
			}
			if(!light_sons.size) data_subtree = T(), size_subtree = 0;
				else data_subtree = light_sons.root -> data, size_subtree = light_sons.root -> size;
			if(son[0]) 
			{
				data_subtree = data_subtree + son[0]->data_subtree;
				size_subtree += son[0] -> size_subtree;
			}
			if(son[1]) 
			{
				data_subtree = data_subtree + son[1]->data_subtree;
				size_subtree += son[1] -> size_subtree;
			}
		}
	};
	
	struct Splay_Node
	{
		AAA_tree *ptr;
		Splay_Node* son[2], *fa;
		int id, size;
		T data, tag;
		int tag_type;//0:no tag;	1:cover_tag;	2:add_tag
		T value() {}//id -> AAA_Node -> data_tot 
		Splay_Node(const AAA_Node &x):ptr(x.ptr), fa(NULL), id(x.id), size(1), data(x.data()), tag_type(0)
		{
			son[0] = son[1] = NULL;
		}
		void change(T delt, int type)//1:cover_tag;	2:add_tag
		{
			ptr -> splay(ptr -> get(id));
			ptr -> get(id) -> change_all(delt, type);
			if(type==1)
			{
				data = size * delt;
				tag = delt;
				tag_type = 1;
			}else//type == 2
			{
				if(tag_type == 0)
				{
					data = data & (size * delt);
					tag = delt;
					tag_type = 2;
				}else//tag_type == 1 or 2
				{
					data = data & (size * delt);
					tag = tag & delt;
				}
			}
		}
		void push_down()
		{
			if(tag_type == 0) return;
			if(son[0]) son[0] -> change(tag, tag_type);
			if(son[1]) son[1] -> change(tag, tag_type);
			tag_type = 0;
		}
		void update()
		{
			size = ptr -> get(id) -> size();
			data = ptr -> get(id) -> data();
			if(son[0]) 
			{
				ptr -> splay(ptr -> get(son[0] -> id));
				size += son[0] -> size;
				data = data + son[0] -> data;
			}
			if(son[1])
			{
				ptr -> splay(ptr -> get(son[1] -> id));
				size += son[1] ->size;
				data = data + son[1] ->data;
			}
		}
	};
	
	struct Splay
	{
		Splay_Node* root;
		int size;
		Splay(){
			size = 0;
			root = NULL;
		}
		~Splay(){
			if(root != NULL) delete root; 
		}
		void clear(){
			delete root;
			root = NULL;
			size = 0;
		}
		Splay_Node * find(int key){
			Splay_Node *now = root;
			while(1){
				if(now == NULL)
					puts("wqnmlgb");
				now -> push_down();
				if(now -> id == key) return now;
				if(key < now -> id) now = now -> son[0];
				else now = now -> son[1];
			}
		}
		void rotate(Splay_Node *x, bool d){
			Splay_Node *k = x -> son[d ^ 1];
			x -> son[d ^ 1] = k -> son[d];
			if(x -> son[d ^ 1] != NULL)
				x -> son[d ^1] -> fa = x;
			k -> son[d] = x;
			k -> fa = x -> fa;
			if(x -> fa != NULL){
				if(x -> fa -> son[0] == x)
					x -> fa -> son[0] = k;
				else if( x -> fa -> son[1] == x)
					x -> fa -> son[1] = k;
			}
			x -> fa = k;
			if(x) x -> update();
			if(k) k -> update(); 
		}
		bool is_root(Splay_Node *p){
			if(p -> fa == NULL) return 1;
			return p -> fa -> son[0] != p && p -> fa -> son[1] != p;
		} 
		void splay(Splay_Node *x){
			if(x != NULL) x -> push_down();
			while(!is_root(x))
			{
				Splay_Node *y = x -> fa;
				bool d1 = x == (y -> son[0]);
				if(is_root(y))
				{
					if(y) y -> push_down();
					if(x) x -> push_down(); 
					rotate(y, d1);
				}
				else 
				{
					Splay_Node *z = y -> fa;
					if(z) z -> push_down();
					if(y) y -> push_down();
					if(x) x -> push_down();
					bool d2 = y == (z -> son[0]);
					if(d1 == d2) 
					{
						rotate(z, d2);
						rotate(y, d1); 
					} 
					else 
					{
						rotate(y, d1);
						rotate(z, d2);
					}
				}
			}
			if (x) x -> update();
			root = x;
		}
		void del(int key){
			Splay_Node *p = root;
			while(1)
			{
				if(p != NULL) p -> push_down();
				if( p -> id == key) break;
				if(key < p -> id) 
					p = p -> son[0];
				else 
					p = p -> son[1];
			}
			splay(p);
			//printf("delete    id = %d tag_type = %d size = %d\n",p->id,p->tag_type,p->size);
			//if(p->son[1])
			//{
			//	printf("son[1]    id = %d tag_type = %d tag = %d data = %d size = %d  \n",p->son[1]->id,p->son[1]->tag_type,p->son[1]->tag,p->son[1]->data,p->son[1]->size);
			//}
			p->push_down();
			size --;
			if(!size) 
			{
				root = NULL;
				return;
			}
			if(p -> son[0] == NULL)
			{
				root = p -> son[1];
				p -> son[1] -> fa = NULL;
				//printf("left is null, id = %d data = %d size = %d\n", root -> id, root -> data, root -> size);
			}
			else if(p -> son[1] == NULL)
			{
				root = p -> son[0];
				p -> son[0] -> fa = NULL;
			}
			else 
			{
				p -> son[0] -> fa = p -> son[1] -> fa = NULL;
				Splay_Node *k = p -> son[0];
				k -> push_down();
				while(k -> son[1] != NULL) {
					k -> push_down();
					k = k -> son[1];
				}
				splay(k);
				k -> son[1] = p -> son[1];
				p -> son[1] -> fa = k;
				root = k;
			}
			
			if(root != NULL) {
				root -> push_down();
				root -> update();
			}
			delete p;
			//printf("id = %d size = %d data = %d tag_type = %d",root->id, root->size, root->data, root->tag_type);
		}//delete node:id=key
		void insert(Splay_Node* &x, Splay_Node * &p){
			if(x != NULL) x -> push_down();
			if(x == NULL)
				x = p;
			else if(p -> id < x -> id){
					insert(x -> son[0], p);
					x -> son[0] -> fa = x;
				}
				 else	{
					insert(x -> son[1], p);
					x -> son[1] -> fa = x;
				}
			x -> update();
		}
		void add(AAA_Node *p){
			size++;
			Splay_Node *k = new Splay_Node(*p);
			insert(root, k);
			splay(k);
		}
	};
	
	void BeRoot(AAA_Node* x)
	{
		access(x);
		//puts("OK_Beroot"); 
		splay(x);
		if(x) x -> downtag_rev();
		root = x;
	}
	
	int size;
	AAA_Node *root;
	AAA_Node **v;

	bool isroot(AAA_Node* x)
	{
		if (x -> fa == 0) return true;
		return x != x -> fa -> son[0] && x != x -> fa -> son[1];
	}

	void rotate(AAA_Node* p, AAA_Node* x)
	{
		bool flag = p == x -> son[1];
		AAA_Node *k = p -> son[flag ^ 1], *g = x -> fa;
		if (k) k -> fa = x;
		if (g)
		{
			if (x == g -> son[0]) g -> son[0] = p;
			if (x == g -> son[1]) g -> son[1] = p;
		}
		p -> fa = g;
		p -> son[flag ^ 1] = x;
		x -> fa = p;
		x -> son[flag] = k;
		if(x) x -> update();
	}
	void splay(AAA_Node* x)
	{
		if (x == 0) return ;
		x -> push_down();
		while (!isroot(x))
		{
			AAA_Node *f = x -> fa, *g = f -> fa;
			if (g) g -> push_down(); 
			if (f) f -> push_down(); 
			if (x) x -> push_down();
			if (isroot(f)) rotate(x, f);
			else if ((x == f -> son[0]) ^ (f == g -> son[0])) rotate(x, f), rotate(x, g);
			else rotate(f, g), rotate(x, f);
		}
		if(x) x -> update();
	}
	void solve_tag(AAA_Node *x){
		if(x == NULL) return ;
		//splay(x);
		AAA_Node * Fa = x;
		while(!isroot(Fa)){
			Fa -> push_down(); 
			Fa = Fa -> fa;
		}
		AAA_Node * LeftNode = Fa;
		LeftNode -> push_down();
		for(;LeftNode -> son[0] != NULL; LeftNode = LeftNode -> son[0])
			LeftNode -> push_down();
		Fa = Fa -> fa;
		if(Fa != NULL)
		{
			Splay_Node * tmp = Fa -> light_sons.find(LeftNode -> id);
			solve_tag(Fa);
			Fa -> light_sons.splay(tmp);
			tmp -> push_down();
		}
		splay(x);
		x -> push_down();
	}
	AAA_Node* access(AAA_Node* x)
	{
		solve_tag(x);
		AAA_Node* v = 0;
		for (; x; v = x, x = x -> fa)
		{
			AAA_Node *tmp = x;
			x -> push_down();
			while(!isroot(tmp)) tmp = tmp -> fa, tmp -> push_down();
			AAA_Node *Fa = tmp -> fa;
			while(1){
				tmp -> push_down();
				if(tmp -> son[0] == NULL) break;
			 	tmp = tmp -> son[0];
			}
			splay(tmp);
			if(Fa != NULL)
			{
				//printf("Before  del  tmp->id = %d  size = %d\n",tmp->id,tmp->size());
				//Print();
				Fa -> push_down();
				//printf("tmp -> id = %d, tmp -> data = %d %d %d\n",tmp->id, tmp->data(), tmp->data_path, tmp->data_subtree);
				Fa -> light_sons.del(tmp -> id);
				//printf("After  del\n");
				//Print();
			}
			splay(x);
			if (x -> son[1]) {
				tmp = x -> son[1];
				while(1){
					tmp -> push_down();
					if(tmp -> son[0] == NULL) break;
					tmp = tmp -> son[0];
				}
				x -> son[1] = NULL;
				splay(tmp);
				//printf("Before add  tmp->id = %d  size = %d\n",tmp->id,tmp->size());
				//Print();
				x -> light_sons.add(tmp);
				//printf("After add\n");
				//Print();
			}
			x -> son[1] = v;
			if(x) x -> update();
		}
		return v;
	}

	AAA_Node* lca(AAA_Node *x, AAA_Node *y)
	{
		access(x);
		return access(y);
	}
public:
	AAA_tree(int n):size(n){
		v = new AAA_Node*[n+1];
		for(int i=0;i<=n;i++)
			v[i]=new AAA_Node(this, i);
	}
	
	AAA_tree(const AAA_tree &other){}
	
	~AAA_tree(){}
	
	AAA_Node* get(int x)
	{
		return v[x];
	}
	
	void add_path(int u, int v, T delt)
	{
		AAA_Node* rt = root;
		AAA_Node *x = get(u), *y = get(v);
		BeRoot(x);
		access(y); 
		splay(y);
		y -> change_path(delt, 2);
		BeRoot(rt);
	}

	void cover_path(int u, int v, T delt)
	{
		AAA_Node* rt = root;
		AAA_Node *x = get(u), *y = get(v);
		BeRoot(x);
		access(y); 
		splay(y);
		y -> change_path(delt, 1);
		BeRoot(rt);
	}
	
	void add_subtree(int x, T delt)
	{
		AAA_Node *xx = get(x);
		access(xx);
		splay(xx);
		if(xx -> light_sons.size) xx -> light_sons.root -> change(delt, 2);
		xx -> val = xx -> val & delt;
		xx -> update();
	}
	
	void cover_subtree(int x, T delt)
	{
		AAA_Node *xx = get(x);
		access(xx);
		splay(xx);
		if(xx -> light_sons.size) xx -> light_sons.root -> change(delt, 1);
		xx -> val = delt;
		xx -> update();
	}
	T ask_path(int u, int v)
	{
		AAA_Node* rt = root;
		AAA_Node *x = get(u), *y = get(v);
		BeRoot(x);
		access(y); splay(y);
		T tmp = y -> data_path;
		BeRoot(rt);
		return tmp;
	}
	
	
	T ask_subtree(int x)
	{
		AAA_Node *xx = get(x);
		access(xx); 
		T tmp;
		if (xx -> light_sons.size) tmp = xx -> light_sons.root -> data;
		else tmp = T();
		return tmp + xx -> val;
	}

	void link(int u, int v)
	{
		AAA_Node* xx = get(u), *yy = get(v);
		BeRoot(xx);
		xx -> fa = yy;
		yy -> light_sons.add(xx);
		if(yy) yy -> update();
		BeRoot(yy);
	}

	void cut(int u)
	{
		AAA_Node* x = get(u);
		access(x); splay(x);
		x -> son[0] -> fa = 0;
		x -> son[0] = 0;
		if(x) x -> update();
	}
	void make_root(int x)
	{
		BeRoot(get(x));
	}
	void change_father(int u, int v)
	{
		AAA_Node* xx = get(u), *yy = get(v);
		if (lca(xx, yy) == xx) return;
		AAA_Node* rt = root;
		cut(u);
		link(u, v);
		BeRoot(rt);
	}
	void yj()
	{
		for(int i=1;i<=size;i++)
		{
			get(i)->push_down();
		}
	}
	void splay_print(Splay_Node * x)
	{
		if(x == NULL) return;
		printf("%d(%d,%d) ",x->id,x->size,x->data);
		splay_print(x->son[0]);
		splay_print(x->son[1]);
	}
	void Print()
	{
		puts("--------------------");
		for(int i=1;i<=size;i++)
		{
			AAA_Node *p=get(i);
			printf("%d rev=%d tag_sub=%d val=%d data_path = %d data_subtree = %d light_sons.size = %d  son[0] = %d  son[1] = %d  fa = %d  root->data = %d  size = %d\n",
			i,p->rev,p->tag_subtree,p->val,
			p->data_path,p->data_subtree,
			p->light_sons.size,p->son[0]==NULL ? 0:p->son[0]->id,p->son[1]==NULL ? 0:p->son[1]->id,
			get(i)->fa==NULL ? 0:get(i)->fa->id,
			p->light_sons.size==0?-1:p->light_sons.root->data,
			p->light_sons.size==0?-1:p->light_sons.root->size);
			printf("      ");splay_print(get(i)->light_sons.root);puts("");
		}
	}
};
}


struct T1//sum
{
	int x;
	T1():x(0){}
	T1(int x):x(x){}
};
T1 operator +(const T1 &a, const T1 &b)
{
	return T1(a.x + b.x);
}
T1 operator &(const T1 &a, const T1 &b)
{
	return T1(a.x + b.x);
}
T1 operator *(const int &a, const T1 &b)
{
	return T1(a * b.x);
}

struct T2//min
{
	int x;
	T2():x(INF){}
	T2(int x):x(x){}
};
T2 operator +(const T2 &a, const T2 &b)
{
	if(a.x < b.x) return a;
	return b;
}
T2 operator &(const T2 &a, const T2 &b)
{
	return T2(a.x + b.x);
}
T2 operator *(const int &a, const T2 &b)
{
	return T2(b.x);
}

struct T3//max
{
	int x;
	T3():x(-INF){}
	T3(int x):x(x){}
};
T3 operator +(const T3 &a, const T3 &b)
{
	if(a.x > b.x) return a;
	return b;
}
T3 operator &(const T3 &a, const T3 &b)
{
	return T3(a.x + b.x);
}
T3 operator *(const int &a, const T3 &b)
{
	return T3(b.x);
}
inline void read(int&a){
  char c;bool f=0;a=0;
  while(!((((c=getchar())>='0')&&(c<='9'))||(c=='-')));
  if(c!='-')a=c-'0';else f=1;
  while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';
  if(f)a=-a;
}
int main()
{
	freopen("sone1.in","r",stdin);
	freopen("sone1.out","w",stdout);
	int n, m, x, y,root;
	scanf("%d%d", &n,&m);
	sjtu::AAA_tree<T1> tree1(n);
	sjtu::AAA_tree<T2> tree2(n);
	sjtu::AAA_tree<T3> tree3(n);
	for (int i = 1; i < n; i ++)
	{
		read(x),read(y);
		tree1.link(x, y);
		tree2.link(x, y);
		tree3.link(x, y);
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		read(x);
		tree1.cover_path(i,i,T1(x));
		tree2.cover_path(i,i,T2(x));
		tree3.cover_path(i,i,T3(x));
	}
	int Root;
	scanf("%d",&Root);
	tree1.make_root(root);
	tree2.make_root(root);
	tree3.make_root(root);
	for(int i=1;i<=m;i++)
	{
		int type,u,v,x;
		read(type);
		if(type == 0){
			read(u),read(x);
			tree1.cover_subtree(u,x);
			tree2.cover_subtree(u,x);
			tree3.cover_subtree(u,x);
		}
		if(type == 1){
			read(u);
			tree1.make_root(u);
			tree2.make_root(u);
			tree3.make_root(u);
		}
		if(type == 2){
			read(u),read(v),read(x);
			tree1.cover_path(u,v,T1(x));
			tree2.cover_path(u,v,T2(x));
			tree3.cover_path(u,v,T3(x));
		}
		if(type == 3){
			read(u);
			T2 ans = tree2.ask_subtree(u);
			printf("%d\n",ans.x);
		}
		if(type == 4){
			read(u);
			T3 ans = tree3.ask_subtree(u);
			printf("%d\n",ans.x);
		}
		if(type == 5){
			read(u),read(x);
			tree1.add_subtree(u,T1(x));
			tree2.add_subtree(u,T2(x));
			tree3.add_subtree(u,T3(x));
		}
		if(type == 6){
			read(u),read(v),read(x);
			tree1.add_path(u,v,T1(x));
			tree2.add_path(u,v,T2(x));
			tree3.add_path(u,v,T3(x));
		}
		if(type == 7){
			read(u),read(v);
			T2 ans = tree2.ask_path(u,v);
			printf("%d\n",ans.x);
		}
		if(type == 8){
			read(u),read(v);
			T3 ans = tree3.ask_path(u,v);
			printf("%d\n",ans.x);
		}
		if(type == 9){
			read(u),read(v);
			tree1.change_father(u,v);
			tree2.change_father(u,v);
			tree3.change_father(u,v);
		}
		if(type == 10){
			read(u),read(v);
			T1 ans = tree1.ask_path(u,v);
			printf("%d\n",ans.x);
		}
		if(type == 11){
			read(u);
			T1 ans = tree1.ask_subtree(u);
			printf("%d\n",ans.x);
		}
		
	}
	return 0;
}
