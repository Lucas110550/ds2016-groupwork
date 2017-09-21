#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"
namespace sjtu {
/**
 * a container like std::priority_queue which is a heap internal.
 */
template<typename T, class Compare = std::less<T> >
class priority_queue {
private:
	struct List_Point;
	struct List;
	struct Root;
	
	Compare cmp;
	
	struct List_Point{
		Root *data;
		List_Point *next;
		List_Point(){}
		List_Point(Root *x, List_Point *p):data(x),next(p){}
		~List_Point(){
			delete data;	
		}
	};
	struct List{
		List_Point *head;
		List(List_Point *p=NULL):head(p){}
		List(const List &other) {
			head = NULL;
			List_Point *tmp_head = NULL, *p = other.head;
			while (p != NULL){
				tmp_head = new List_Point(new Root(*(p->data)),tmp_head);
				p = p->next;	
			}
			while (tmp_head!=NULL)
			{
				List_Point *p=tmp_head;
				tmp_head = p->next;
				p->next = head;
				head = p;
			}
		}
		~List(){
			while(head != NULL){
				List_Point *p = head;
				head = p->next;
				delete p;
			}
		}
		const List &operator = (const List &other){
			if(this == &other) return *this;
			head = NULL;
			List_Point *tmp_head = NULL, *p = other.head;
			while (p != NULL){
				tmp_head = new List_Point(new Root(*(p->data)),tmp_head);
				p = p->next;	
			}
			while (tmp_head!=NULL)
			{
				List_Point *p=tmp_head;
				tmp_head = p->next;
				p->next = head;
				head = p;
			}
			return *this;
		}
		void add(Root *x){
			head = new List_Point(x, head);
		}
		void erase(List_Point *x){
			if(head == x){
				head = x->next;
			}else{
				List_Point *p = head;
				while (p->next != x) p = p->next;
				p->next = x->next;
			}
		}
	};
	struct Root{
		T key;
		size_t deg;
		List child;	
		Root(const T &x):key(x), deg(0){
			child.head = NULL;
		}
		Root(const Root &other):key(other.key), deg(other.deg), child(other.child){}
	};
	size_t num_tot;
	List child;
	
	//merge Root_a and Root_b return Root*
	Root* merge_root(Root *&x, Root *&y){//Attention: It must be Root *&
		if (!cmp((y->key),(x->key))) {
			Root *z = x;
			x=y;
			y=z;
		}
		(x->deg)++;
		(x->child).add(y);
		y=NULL;
		return x;
	}
	//add List_Point_p to List_a
	void add_in_List(List_Point *p, List &a){
		while (a.head != NULL && ((a.head)->data)->deg == (p->data)->deg){
			p->data = merge_root(p->data, (a.head)->data);
			List_Point *tmp = a.head;
			a.head = tmp->next;
			delete tmp;
		}
		p->next = a.head;
		a.head = p;
	}
	
	//add List_b to List_a
	void merge_List(List &a,List &b){
		List tmp;
		while (a.head != NULL || b.head != NULL){
			if (a.head!=NULL && (b.head == NULL || ((a.head)->data)->deg > ((b.head)->data)->deg)){
				List_Point *p = a.head;
				a.head = p->next;
				add_in_List(p, tmp);
			}else{
				List_Point *p = b.head;
				b.head = p->next;
				add_in_List(p, tmp);
			}
		}
		while (tmp.head != NULL){
			List_Point *p = tmp.head;
			tmp.head = p->next;
			p->next = a.head;
			a.head = p;
		}
	}
	List_Point* top_List_Point() const{
		List_Point *p = child.head;
		List_Point *tmp = child.head;
		while (p != NULL){
			if (!cmp(((p->data)->key) , ((tmp->data)->key) )) tmp = p;
			p = p->next;
		}
		return tmp;
	}
public:
	/**
	 * TODO constructors
	 */
	priority_queue():num_tot(0){}
	priority_queue(const priority_queue<T, Compare> &other):num_tot(other.num_tot), child(other.child){}
	/**
	 * TODO deconstructor
	 */
	~priority_queue() {}
	/**
	 * TODO Assignment operator
	 */
	priority_queue<T, Compare> &operator=(const priority_queue<T, Compare> &other) {
		if(this == &other) return *this;
		this -> ~priority_queue();
		num_tot = other.num_tot;
		child = other.child;
		return *this;
	}
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const{
		if(!num_tot) throw container_is_empty();
		return (top_List_Point()->data)->key;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {
		num_tot++;
		List tmp(new List_Point(new Root(e),NULL));
		merge_List(child,tmp);
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop(){
		if(num_tot==0) throw container_is_empty();
		num_tot--;
		List_Point *tmp = top_List_Point();
		child.erase(tmp);
		merge_List(child,(tmp->data)->child);
		delete tmp;
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {
		return num_tot;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {
		return num_tot == 0;
	}
};


}

#endif
