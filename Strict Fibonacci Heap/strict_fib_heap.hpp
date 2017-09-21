#ifndef SJTU_strict_fib_heap_HPP
#define SJTU_strict_fib_heap_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>
#include "exceptions.hpp"
using namespace std;
namespace sjtu {
#define ptr shared_ptr


/**
 * a container like std::strict_fib_heap which is a heap internal.
 */
template<typename T, class Compare = std::less<T> >
class strict_fib_heap {
	Compare cmp;
	struct Node;
	struct Q_Point;
	struct Rank_Point;
	struct Fix_Point;
	struct Q_List;
	struct Node_List;
	struct Rank_List;
	struct Fix_List;
	struct Active_Record;
	
	struct Node{
		ptr<Node> pre, next, fa;
		int loss;
		T key;
		ptr<Active_Record> active;
		ptr<Rank_Point> rank;
		ptr<Fix_Point> fix;
		ptr<Q_Point> pos;
		Node_List ch;
		Node() :loss(0){
			fix.reset();
			rank.reset();
			active.reset();
			pre.reset();
			next.reset();
			fa.reset();
		}
		Node(T value):key(value),loss(0){;	
			fix.reset();
			rank.reset();
			active.reset();
			pre.reset();
			next.reset();
			fa.reset();
		}
	};
	struct Q_Point{
		ptr<Q_Point> pre,next;
		ptr<Node> node;	
		Q_Point(){
			node.reset();
			pre.reset();
			next.reset();
		}
		Q_Point(const ptr<Node> &x):node(x){}
	};
	struct Rank_Point{
		ptr<Fix_Point> loss, active_root;	
		ptr<Rank_Point> pre, next;
		Rank_Point(){
			loss.reset();
			active_root.reset();
			pre.reset();
			next.reset();
		}
	};
	struct Fix_Point{
		ptr<Rank_Point> rank;
		ptr<Node> node;	
		ptr<Fix_Point> pre, next;
		Fix_Point(){
			rank.reset();
			node.reset();
			pre.reset();
			next.reset();
		}
	};
	
	struct Node_List
	{
		int size;
		ptr<Node> tail;
		Node_List():size(0){
			tail.reset();
		}
		void swap(Node_List &a)
		{
			std::swap(size, a.size);
			swap(tail, a.tail);
		}
		ptr<Node> front()
		{
			if(empty()) 
				return NULL;
			return tail -> next;
		}
		bool empty()
		{
			return size == 0;
		}
		int Size()
		{
			return size;
		}
		void Insert_front(ptr<Node> x)
		{
			if(!size)
			{
				tail = x;
				tail -> pre = tail -> next = tail;
			}
			else 
			{
				ptr<Node> tmp = x;
				tmp -> pre = tail;
				tmp -> next = tail -> next;
				(tail -> next) -> pre = tmp;
				tail -> next = tmp;
			}
			++size;
		}
		void Insert_back(ptr<Node> x)
		{
			if(!size)
			{
				tail = x;
				tail->pre = tail -> next = tail;
			}
			else 
			{
				ptr<Node> tmp = x;
				tmp -> pre = tail;
				tmp -> next = tail -> next;
				(tail -> next) -> pre = tmp;
				tail -> next = tmp;
				tail = tmp;
			}
			++size;
		}
		void Insert(ptr<Node> pos, ptr<Node> x)
		{
			if(!size)
				tail = x;
			else 
			{
				ptr<Node> tmp = x;
				tmp -> pre = pos;
				tmp -> next = pos -> next;
				(pos -> next) -> pre = tmp;
				pos -> next = tmp;
				if(pos == tail) tail = tmp;
			}
			++size;
		}
		void Delete(ptr<Node> pos){
			if(pos == NULL) return ;
			if(size == 1) tail.reset();
			else 
			{
				if(tail == pos)
					tail = tail -> pre;	
				(pos -> pre) -> next = (pos -> next);
				(pos -> next) -> pre = (pos -> pre);
			}
			--size;
		}
	};
	struct Rank_List
	{
		int size;
		ptr<Rank_Point> tail;
		Rank_List(){
			size = 0;
			tail.reset();
			ptr<Rank_Point> get = make_shared<Rank_Point>();
			Rank_List::Insert_back(get);
		}
		ptr<Rank_Point> front()const
		{
			if (tail == NULL) return NULL;
			return tail -> next;
		}
		void swap(Rank_List &a)
		{
			std::swap(size, a.size);
			tail.swap(a.tail);
		}
		bool empty()const
		{
			return size == 0;
		}
		int Size()const
		{
			return size;
		}
		void Insert_front(ptr<Rank_Point> x)
		{
			if(!size)
			{
				tail = x;
				tail -> pre = tail -> nex = tail;
			}
			else 
			{
				ptr<Node> tmp = x;
				tmp -> pre = tail;
				tmp -> next = tail -> next;
				(tail -> next) -> pre = tmp;
				tail -> next = tmp;
			}
			++size;
		}
		void Insert_back(ptr<Rank_Point> x)
		{
			if(!size)
			{
				tail = x;
				tail->pre = tail -> next = tail;
			}
			else 
			{
				ptr<Rank_Point> tmp = x;
				tmp -> pre = tail;
				tmp -> next = tail -> next;
				(tail -> next) -> pre = tmp;
				tail -> next = tmp;
				tail = tmp;
			}
			++size;
		}
		void Insert(ptr<Rank_Point> pos, ptr<Rank_Point> x)
		{
			if(!size)
				tail = x;
			else 
			{
				ptr<Rank_Point> tmp = x;
				tmp -> pre = pos;
				tmp -> next = pos -> next;
				(pos -> next) -> pre = tmp;
				pos -> next = tmp;
				if(pos == tail) tail = tmp;
			}
			++size;
		}
		void Delete(ptr<Rank_Point> pos){
			if(pos == NULL) return ;
			if(size == 1)tail.reset();
			else 
			{
				if(tail == pos)
					tail = tail -> pre;	
				(pos -> pre) -> next = (pos -> next);
				(pos -> next) -> pre = (pos -> pre);
			}
			--size;
		}
	};
	struct Fix_List
	{
		int size;
		ptr<Fix_Point> tail;
		Fix_List(){
			size = 0;
			tail.reset();
		}
		ptr<Fix_Point> front()
		{
			if (tail == NULL) return 0;
			return tail -> next;
		}
		bool empty()const
		{
			return size == 0;
		}
		void swap(Fix_List &a)
		{
			std::swap(size, a.size);
			tail.swap(a.tail);
		}
		int Size()const
		{
			return size;
		}
		void Insert_front(ptr<Fix_Point> x)
		{
			if(!size)
			{
				tail = x;
				tail -> pre = tail -> next = tail;
			}
			else 
			{
				ptr<Fix_Point> tmp = x;
				tmp -> pre = tail;
				tmp -> next = tail -> next;
				(tail -> next) -> pre = tmp;
				tail -> next = tmp;
			}
			++size;
		}
		void Insert_back(ptr<Fix_Point> x)
		{
			if(!size)
			{
				tail = x;
				tail->pre = tail -> next = tail;
			}
			else 
			{
				ptr<Fix_Point> tmp = x;
				tmp -> pre = tail;
				tmp -> next = tail -> next;
				(tail -> next) -> pre = tmp;
				tail -> next = tmp;
				tail = tmp;
			}
			++size;
		}
		void Insert(ptr<Fix_Point> pos, ptr<Fix_Point> x)
		{
			if(!size)
				tail = x;
			else 
			{
				ptr<Fix_Point> tmp = x;
				tmp -> pre = pos;
				tmp -> next = pos -> next;
				(pos -> next) -> pre = tmp;
				pos -> next = tmp;
				if(pos == tail)	tail = tmp;
			}
			++size;
		}
		void Delete(ptr<Fix_Point> pos)
		{
			if(pos == NULL) return ;
			if(size == 1)tail.reset();
			else 
			{
				if(tail == pos)
					tail = tail -> pre;	
				(pos -> pre) -> next = (pos -> next);
				(pos -> next) -> pre = (pos -> pre);
			}
			--size;
		}
	};
	struct Q_List
	{
		int size;
		ptr<Q_Point> tail;
		Q_List(){
			size = 0;
			tail.reset();
		}
		ptr<Q_Point> front()
		{
			if (tail == NULL) return 0;
			return tail -> next;
		}
		bool empty()const 
		{
			return size == 0;
		}
		void swap(Q_List &a)
		{
			std::swap(size, a.size);
			tail.swap(a.tail);
		}
		int Size()const
		{
			return size;
		}
		void Insert_back(ptr<Q_Point> x)
		{
			if(!size)
			{
				tail = x;
				tail->pre = tail -> next = tail;
			}
			else 
			{
				ptr<Q_Point> tmp(x);
				tmp -> pre = tail;
				tmp -> next = tail -> next;
				(tail -> next) -> pre = tmp;
				tail -> next = tmp;
				tail = tmp;
			}
			++size;
		}
		
		void Delete(ptr<Q_Point> pos)
		{
			if(pos == NULL) return ;
			if(size == 1)tail.reset();
			else 
			{
				if(tail == pos)
					tail = tail -> pre;
				(pos -> pre) -> next = (pos -> next);
				(pos -> next) -> pre = (pos -> pre);
			}
			--size;
		}
		void Merge(const Q_List &other)
		{
			if(other.empty()) return;
			if(empty())
			{
				tail = other.tail;
				size = other.size;
				return ; 
			}
		//默认为头尾相连
			(tail->next) -> pre = other.tail;
			(other.tail->next) -> pre = tail;
			ptr<Q_Point> tmp= other.tail -> next;
			other.tail -> next = tail -> next;
			tail -> next = tmp;
			size += other.size;
			tail = other.tail;
		}
	};
	struct Active_Record{
		bool flag;	
		Active_Record():flag(true){}
	};
	
	ptr<Active_Record> active_record;
	int tot_size;
	ptr<Node> root, not_linkable_child;
	Q_List Q;
	Fix_List part1, part2, part3, part4;
	Rank_List rank;
	
	void link(ptr<Node> x, ptr<Node> y)//link:x->y
	{
		x -> fa = y;
		if (is_active(x))
		{
			if (is_active(y)) increase_rank(y);
			else
			{
				if (is_linkable(y)) make_passive(y);
				make_active_root(x);
			}
			(y -> ch).Insert_front(x);
		}
		else//x is passive
		{
			if (y == root)
			{
				if ((root -> ch).empty())
				{
					(root -> ch).Insert_front(x);
					not_linkable_child = (root -> ch).tail;
				}
				else
				{
					(root -> ch).Insert(not_linkable_child, x);
					if (!is_linkable(x)) not_linkable_child = not_linkable_child -> next;
				}
			}
			else
			{
				(y -> ch).Insert_back(x);
			}
		}
	}
	
	void cut(ptr<Node> x)//cut x from its father
	{
		ptr<Node> y = x -> fa;
		if (y == root)
		{
			if (x == not_linkable_child)
			{
				if ((y -> ch).Size() == 1) not_linkable_child.reset();
				else not_linkable_child = not_linkable_child->pre;
			}
			if (is_active(x))//x is active_root
			{
				make_active(x);
			}
			(y -> ch).Delete(x);
		}
		else
		{
			(y -> ch).Delete(x);
			if (is_active(x))
			{
				if (is_active_root(x))//y is passive
				{
					make_active(x);
					if ((y -> ch).empty() || !is_active((y -> ch).front()))
					{
						make_linkable(y);
					}
				}
				else//y is active
				{
					decrease_rank(y);
					if(!is_active_root(y)) increase_loss(y);
				}
			}
		}
		x -> fa = 0;
	}
	void opt_A(ptr<Node> x, ptr<Node> y)
	{
		if(cmp(x -> key,y -> key)) 
			x.swap(y);
		cut(y);
		link(y, x);
		ptr<Node> z = (x -> ch).tail;	
		if (!z) return ;
		if(!is_active(z))
		{
			cut(z);
			link(z, root);
		}
	}
	bool opt_R()
	{
		if ((root -> ch).Size() < 3) return 0;
		ptr<Node> x = (root -> ch).tail, y = x -> pre, z = y -> pre;
		if (is_linkable(x) && is_linkable(y) && is_linkable(z))
		{
			if(cmp(x -> key, y -> key)) swap(x, y);
			if(cmp(y -> key, z -> key)) swap(y, z);
			if(cmp(x -> key, y -> key)) swap(x, y);
			cut(y);
			cut(z);
			make_linkable_to_active(x);
			make_linkable_to_active(y);
			make_active_root(x);
			link(z, y);
			link(y, x);
			return 1;
		}

		return 0;
	}
	void opt_L1(ptr<Node> x)
	{
		if(!is_active_root(x) && x -> loss >= 2)
			cut(x), link(x, root);
	}
	void opt_L2(ptr<Node> x, ptr<Node> y)
	{
		if (cmp(x -> key, y -> key)) swap(x, y);
		cut(y); link(y, x);
		loss_set_to_zero(x);
		loss_set_to_zero(y);
	}
	bool is_active(ptr<Node> x){
		if(x->active == NULL) return 0;
		return (x->active)->flag;
	}
	bool is_passive(ptr<Node> x){
		if(x->active == NULL) return 1;
		return !(x->active)->flag;
	}
	bool is_active_root(ptr<Node> x){
		if(!is_active(x)) return 0;
		return (!is_active(x->fa));
	}
	bool is_linkable(ptr<Node> x){
		if(is_active(x)) return 0;
		if((x->ch).empty()) return 1;
		return (!is_active((x->ch).front()));
	}
	void make_active_to_passive(ptr<Node> x)
	{
		if (!is_active_root(x)) loss_set_to_zero(x);
		else delete_from_fix_list(x);
		x -> rank = 0, x -> fix = 0;
		x -> active = 0; 
	}
	void make_active_root(ptr<Node> x) // 需要优先保证parent是passive类, x是active类。 
	{
		//if (x == root) throw invalid_operation1{};
		//if (is_active(x) == false) throw invalid_operation2{};
		//if (is_active(x -> fa) == true) throw invalid_operation3{};
		ptr<Fix_Point> tmp;
		loss_set_to_zero(x);
		insert_to_fix_list(x);
	}
	void make_active(ptr<Node> x) { delete_from_fix_list(x); }
	void make_linkable_to_active(ptr<Node> x)
	{
		//if (x == root) throw invalid_operation4{};
		x -> loss = 0;
		x -> active = active_record;
		if (x -> fa && is_linkable(x -> fa)) make_passive(x -> fa);
		x -> rank = rank.tail -> next;
		x -> fix = 0;
		ptr<Node> y(x->fa);
		if (y == 0) return ;
		if(not_linkable_child == x)
			(y -> ch).tail = (y -> ch).tail -> pre;
		else
		{
			(y -> ch).Delete(x);
			(y -> ch).Insert_front(x);
			if (is_linkable(not_linkable_child))
				not_linkable_child = x;	
		}
	}
	void make_passive(ptr<Node> x)
	{
		if (x == root) return;
		ptr<Node> y(x -> fa);
		if (y == 0) return;
		if(y == root)
		{
			if((y -> ch).Size()==1) return;
			if(x == not_linkable_child) not_linkable_child = not_linkable_child -> pre;
			(y -> ch).Delete(x);
			(root -> ch).Insert(not_linkable_child, x);
			not_linkable_child = x;
		}
	}
	void make_linkable(ptr<Node> x)//passive -> linkable
	{
		if(x==root) return;
		ptr<Node> y(x -> fa);
		if (y == 0) return ;
		if(y == root)
		{
			if(x == not_linkable_child)
			{
				not_linkable_child = not_linkable_child -> pre;
			}else
			{
				(y -> ch).Delete(x);
				(root -> ch).Insert(not_linkable_child, x);
			}
		}
	}
	void increase_rank(ptr<Node> x)
	{
		bool mark = false;
		if (x -> fix) 
			delete_from_fix_list(x), mark = true;
		if (x -> rank == rank.tail)
		{
			ptr<Rank_Point> get = make_shared<Rank_Point>();
			rank.Insert_back(get);
		}
		x -> rank = x -> rank -> next;
		if (mark) insert_to_fix_list(x);
	}
	void decrease_rank(ptr<Node> x)
	{
		bool mark = false;
		if (x -> fix)
			delete_from_fix_list(x), mark = true;
	 	//if (x -> rank == rank.tail -> next) throw invalid_operation5{};
		x -> rank = x -> rank -> pre;
		if (mark) insert_to_fix_list(x);
	}
	void loss_set_to_zero(ptr<Node> x)
	{
		if (x -> loss == 0) return ;
		delete_from_fix_list(x);
		x -> loss = 0;
	}
	void increase_loss(ptr<Node> x) //sure x is a active node but not a active root
	{
		int num = x -> loss;
		loss_set_to_zero(x);
		x -> loss = num + 1;
		insert_to_fix_list(x);
	}
	void insert_to_fix_list(ptr<Node> x) // be sure x is not in fix_list
	{
		ptr<Fix_Point> tmp(make_shared<Fix_Point>());
		tmp -> node = x;
		tmp -> rank = x -> rank;
		x -> fix = tmp;
	//	if (x -> fix) printf("ok\n");
		x -> rank = 0;
		if (is_active_root(x))
		{
			if (tmp -> rank -> active_root == 0)
			{
				tmp -> rank -> active_root = tmp;
				part2.Insert_front(tmp);
			}
			else
			{
				ptr<Fix_Point> cur = tmp -> rank -> active_root;
				if (is_part2(cur))
				{
					part2.Delete(cur);
					tmp -> rank -> active_root = 0;
					part1.Insert_front(cur);
					part1.Insert_front(tmp);
					tmp -> rank -> active_root = tmp;
				}
				else part1.Insert(cur, tmp);
			}
		}
		else if (x -> loss)
		{
			if (tmp -> rank -> loss == 0)
			{
				tmp -> rank -> loss = tmp;
				if (x -> loss == 1) part3.Insert_front(tmp);
				else part4.Insert_front(tmp);
			}
			else
			{
				ptr<Fix_Point> cur = tmp -> rank -> loss;
				if (is_part3(cur))
				{
					part3.Delete(cur);
					tmp -> rank -> loss = 0;
					part4.Insert_back(cur);
					part4.Insert_back(tmp);
				}
				else part4.Insert(cur, tmp);
				tmp -> rank -> loss = tmp;
			}
		}
	}
	void delete_from_fix_list(ptr<Node> x) // be sure x is in fix_list
	{
		ptr<Fix_Point> tmp = x -> fix;
		x -> rank = tmp -> rank;
		x -> fix = 0;
		if (is_active_root(x))
		{
			if (is_part1(tmp))
			{
				if (tmp -> rank -> active_root == tmp)
					tmp -> rank -> active_root = tmp -> next;
				part1.Delete(tmp);
				ptr<Fix_Point> cur = tmp -> rank -> active_root;
				if (cur -> next == cur || cur -> next -> rank != cur -> rank)
					part1.Delete(cur), part2.Insert_front(cur);
			}
			else
			{
				part2.Delete(tmp);
				tmp -> rank -> active_root = 0;
			}
		}
		else
		{
			ptr<Fix_Point> cur = tmp -> rank -> loss;
			if (is_part4(tmp))
			{
				if (cur -> pre == cur || cur -> pre -> rank != cur -> rank)
					tmp -> rank -> loss = 0;
				else
				{
					if (cur == tmp) cur = cur -> pre;
					tmp -> rank -> loss = cur;
					part4.Delete(tmp);
					if (cur -> pre == cur || cur -> pre -> rank != cur -> rank)
					{
						if (cur -> node -> loss < 2)
							part4.Delete(cur), part3.Insert_front(cur);
					}
				}
			}	
			else
			{
				part3.Delete(tmp);
				tmp -> rank -> loss = 0;
			}
		}
	}
	bool A()
	{
		if (part1.tail == 0) return false;
		ptr<Fix_Point> x = part1.front();
		ptr<Fix_Point> y = x -> next;
		opt_A(x -> node, y -> node);
		return true;
	}
	bool L()
	{
		if (part4.tail == 0) return false;
		ptr<Fix_Point> cur = part4.tail;
		if (cur -> node -> loss >= 2) opt_L1(cur -> node);
		else
		{
			ptr<Fix_Point> y = cur -> pre;
			if (y -> node -> loss >= 2) opt_L1(y -> node);
			else opt_L2(y -> node, cur -> node);
		}
		return true;
	}
	bool is_part1(ptr<Fix_Point> x)
	{
		if (x -> next == x) return false;
		if (x -> next -> rank == x -> rank || x -> pre -> rank == x -> rank) return true;
		return false;
	}
	bool is_part2(ptr<Fix_Point> x) { return !is_part1(x); }
	bool is_part4(ptr<Fix_Point> x)
	{
		if (x -> pre != x && (x -> pre -> rank == x -> rank || x -> next -> rank == x -> rank)) return true;
		if (x -> node -> loss >= 2) return true;
		return false;
	}
	bool is_part3(ptr<Fix_Point> x) { return !is_part4(x); }
	//void decrease_key(ptr<Node> x, const T){}  pending......
	
public:
	/**
	 * TODO constructors
	 */
	strict_fib_heap() :tot_size(0),active_record(make_shared<Active_Record>()){}
	strict_fib_heap(const T &e):active_record(make_shared<Active_Record>()), tot_size(1), root(make_shared<Node>(e)){}
	strict_fib_heap(strict_fib_heap<T, Compare> &other): active_record(make_shared<Active_Record>()),tot_size(0){
		std::vector<T> vec;
		while (!other.empty())
		{
			vec.push_back(other.top());
			other.pop();
		}
		for(int i = 0; i < (int)vec.size(); i ++)
		{
			other.push(vec[i]);
			push(vec[i]);
		}
	}
	~strict_fib_heap() {}
	/**
	 * TODO Assignment operator
	 */
	strict_fib_heap<T, Compare> &operator=(strict_fib_heap<T, Compare> &other) {
		if(this == &other) return *this;
		this -> ~strict_fib_heap();
		tot_size = 0;
		active_record = make_shared<Active_Record>();
		std::vector<T> vec;
		while (!other.empty())
		{
			vec.push_back(other.top());
			other.pop();
		}
		for(int i = 0;i < (int)vec.size();i++)
		{
			other.push(vec[i]);
			push(vec[i]);
		}
		return *this;
	}
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const {
		if(tot_size == 0) throw container_is_empty();
		return root -> key;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {
		strict_fib_heap tmp(e);
		merge(tmp);
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() {
		if(tot_size == 0) throw container_is_empty();
		tot_size --;
		if (tot_size == 0) { root = 0; return ;}
		ptr<Node> cur = (root -> ch).front();
		bool flag = false;
		ptr<Node> now;
		for (ptr<Node > i = cur; i; i = i -> next)
		{
			if (flag == false) now = i, flag = true;
			else if (cmp(now -> key, i -> key)) now = i;
			if (i -> next == cur) break;
		}
		if (is_active(now))
		{
			make_active_to_passive(now);	
			if (!(now -> ch).empty())
			{
				for (ptr<Node > i = (now -> ch).front(); ; i = i -> next)
				{
					if (is_active(i)) make_active_root(i);
					if (i -> next == (now -> ch).front()) break;
				}
			}
		}
		cut(now);
		cur = (root -> ch).front();
		now -> fa = 0;
		for (ptr<Node > i = cur; i; )
		{
			ptr<Node > tmp = i -> next;
			bool mark = false;
			if (i == tmp) mark = true;
			cut(i);
			link(i, now);
			if (mark) break;
			i = tmp;
		}
		root = now;
		cur = (now -> ch).tail;
		ptr<Node > last = 0;
		for (ptr<Node > i = cur; i; )
		{
			ptr<Node > tmp = i -> pre;
			bool mark = false;
			if (tmp == (now -> ch).tail) mark = true;
			if (is_linkable(i)) now -> ch.Delete(i), now -> ch.Insert_back(i), last = i;
			else if (is_active(i)) break;
			if (mark) break;
			i = tmp;
		}
		cur = (now -> ch).tail;
		for (ptr<Node > i = cur; i; i = i -> pre)
		{
			if (!is_linkable(i)) { not_linkable_child = i; break; }
			if (i -> pre == cur) break;
		}
		if (not_linkable_child == 0) not_linkable_child = cur;
		Q.Delete(now -> pos);
	//	printf("*%d\n", Q.Size());
		if (!Q.empty())
		{
			ptr<Node> p = Q.front() -> node;
			ptr<Node> yy = (p -> ch).tail;
			if (yy)
			{
				ptr<Node> xx = yy -> next;
				if (is_passive(yy)) cut(yy), link(yy, now);
				if (yy != xx && is_passive(xx)) cut(xx), link(xx, now);
				Q.tail = Q.tail -> next;
			}
			p = Q.front() -> node;
			yy = (p -> ch).tail;
			if (yy)
			{
				ptr<Node> xx = yy -> next;
				if (is_passive(yy)) cut(yy), link(yy, now);
				if (yy != xx && is_passive(xx)) cut(xx), link(xx, now);
				Q.tail = Q.tail -> next;
			}
		}
		for (; L(); );
		for (; A(); );
		for (; opt_R(); );
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {
		return tot_size;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {
		return tot_size == 0;
	}
	void merge(strict_fib_heap &other){
		if(this == &other) return;
		if(tot_size < other.tot_size)
		{
			swap(tot_size, other.tot_size);
			swap(root, other.root);
			swap(not_linkable_child, other.not_linkable_child);
			Q.swap(other.Q);
			rank.swap(other.rank);
			part1.swap(other.part1);
			part2.swap(other.part2);
			part3.swap(other.part3);
			part4.swap(other.part4);
			active_record.swap(other.active_record);
		} 
		if(other.tot_size == 0) return;
		(other.active_record) -> flag = false;
		ptr<Node> u(root), v(other.root);
		if(cmp(u -> key, v -> key)) swap(u,v);
		Q.Insert_back(make_shared<Q_Point>(v));
		v->pos = Q.tail;
		Q.Merge(other.Q);
		root = u; link(v, u);
		tot_size += other.tot_size;
		A();
		opt_R();
		int y=1;
	}
	int Rank_Size()
	{
		return rank.Size();
	}
};


}
#endif
