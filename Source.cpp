
//DATA STRUCTURES

#include <iostream>
using namespace std;

class Item
{
public:
	int val;
	Item *next, *pre;
	Item()
	{
		val = 0;
		next = 0;
		pre = 0;


	}
	Item(int val)
	{
		this->val = val;
		next = 0;
		pre = 0;
	}

};

class DLinkedList
{

	int size;
	Item *front;
	Item *back;

public:

	DLinkedList();
	DLinkedList(const DLinkedList &list);

	void push_back(Item *a);
	void push_front(Item *a);

	Item * pop_front();
	Item * pop_back();
	Item * pop_at(int t); //removes t-th element
	Item * pop_this(Item *a); //removes item a in list

	void insert(Item *a, int t); // insert the item a after the t-th element
	void insertlist(DLinkedList *list, int t); // insert the whole list after the t-th element
	void display(ostream &out);

	int getSize();
	int findindex(Item *a);
	Item * getfront();
	Item * getback();
	void swap(Item *p, Item *q); //swap two items pointed by p and q, you can assume that p and q are something in the list

	Item * extractmin(Item * start); // return the pointer of the min element after  "start",
									 // here you can assume user will always input a valid pointer start that points to an item in the list
	Item * extractmax(Item * start);  // return the pointer of the max element after "start"

};

class myStack
{
	DLinkedList list;
public:
	myStack();
	int getSize();
	void in(Item *a);
	Item *top();
	Item *out(); //note: i decided to return an Item when popping from stack or queue to maximize usefulness
	void display(ostream &out); //custom stack display

};

class myQueue
{
	DLinkedList list;
public:
	myQueue();
	int getSize();
	void in(Item *a);
	Item *front();
	Item *out();
	void display(ostream &out); //custom queue display
};

//****************************************//
//*****************DDLIST*****************//
//****************************************//
DLinkedList::DLinkedList()
{
	front = NULL;
	back = NULL;
	size = 0;
}

//Now thats what I call a Deep Copy
DLinkedList::DLinkedList(const DLinkedList &list)
{
	Item *current = list.front;
	front = NULL;
	back = NULL;
	while (current != nullptr) {
		push_back(new Item(current->val));
		current = current->next;
	}
}

void DLinkedList::push_back(Item *a)
{
	if (front == NULL) {
		a->pre = NULL;
		a->next = NULL;
		front = a;
	}
	else if(front->next == NULL){
		a->pre = front;
		a->next = NULL;
		back = a;
		front->next = back;
	}
	else {
		back->next = a;
		a->pre = back;
		a->next = NULL;
		back = a;
	}
	size = getSize();
}

void DLinkedList::push_front(Item *a)
{
	if (front == NULL) {
		a->pre = NULL;
		a->next = NULL;
		front = a;
	}
	else if (front->next == NULL) {
		a->pre = NULL;
		a->next = front;
		back = front;
		front = a;
		back->pre = front;
	}
	else {
		front->pre = a;
		a->next = front;
		a->pre = NULL;
		front = a;
	}
	size = getSize();
}

Item * DLinkedList::pop_front() {
	Item* current = front;
	front = front->next;
	if (front != nullptr) {
		front->pre = NULL;
	}
	return current;
}

Item * DLinkedList::pop_back() {
	Item* current;
	if (back == nullptr) {
		current = front;
		front = NULL;
	}
	else {
		current = back;
		back = back->pre;
		back->next = NULL;
	}
	return current;
}

Item * DLinkedList::pop_at(int t) {
	Item *current = front;
	for (int i = 1; i < t; i++) {
		current = current->next;
	}
	if (current->next == nullptr) return pop_back();
	if (current->pre == nullptr) return pop_front();
	current->pre->next = current->next;
	current->next->pre = current->pre;
	return current;
}

Item * DLinkedList::pop_this(Item* a) {
	return pop_at(findindex(a));
}

void DLinkedList::insert(Item *a, int t) {
	Item *current = front;
	if (current == nullptr||t == 0) {
		push_front(a);
	}
	else if (current->next == nullptr|| t > getSize()) {
		push_back(a);
	}
	else {
		for (int i = 1; i < t; i++) {
			current = current->next;
		}
		current->next->pre = a;
		a->next = current->next;
		a->pre = current;
		current->next = a;
	}
	size = getSize();
}

void DLinkedList::insertlist(DLinkedList *list, int t) {
	Item *current = front;
	for (int i = 1; i < t; i++) {
		current = current->next;
	}
	if (current->next == nullptr) {
		back->next = list->front;
		front->pre = back;
	}
	else {
		current->next->pre = list->back;
		list->back->next = current->next;
		list->front->pre = current;
		current->next = list->front;
	}
	size = getSize();
}

void DLinkedList::display(ostream &out)
{
	Item *current = front;
	while (current != nullptr) {
		if (current->next == NULL) {
			out << current->val;
		}
		else {
			out << current->val << ", ";
		}
		current = current->next;
	}
}

int DLinkedList::getSize()
{
	Item *current = front;
	size = 0;
	while (current != nullptr) {
		current = current->next;
		size++;
	}
	return size;
}

int DLinkedList::findindex(Item *a) {
	Item * current = front;
	int t = 1;
	while (current != a) {
		current = current->next;
		t++;
	}
	return t;
}

Item * DLinkedList::getfront() {
	return this->front;
}

Item * DLinkedList::getback() {
	return this->back;
}

void DLinkedList::swap(Item *p, Item *q) {
	int indexp = findindex(p) - 1;
	int indexq = findindex(q) - 1;
	Item * currp = pop_this(p);
	Item * currq = pop_this(q);
	if (indexp < indexq) {
		insert(currq, indexp);
		insert(currp, indexq);
	}
	else {
		insert(currp, indexq);
		insert(currq, indexp);
	}
}

Item * DLinkedList::extractmin(Item * start) {
	Item * current = start->next;
	Item * min = start->next;
	while (current != nullptr) {
		if (min->val > current->val) min = current;
		current = current->next;
	}
	return min;
}

Item * DLinkedList::extractmax(Item * start) {
	Item * current = start->next;
	Item * max = start->next;
	while (current != nullptr) {
		if (max->val < current->val) max = current;
		current = current->next;
	}
	if (max == nullptr)
	{
		return NULL;
	}
	return max;
}

//****************************************//
//*****************STACKS*****************//
//****************************************//
myStack::myStack() { }

int myStack::getSize() {
	return list.getSize();
}

void myStack::in(Item *a) {
	list.push_back(a);
}

Item * myStack::top() {
	return list.getback();
}

Item * myStack::out() {
	return list.pop_back();
}

void myStack::display(ostream &out) {
	Item *current = list.getback();
	while (current != nullptr) {
		out << '|' << current->val << "|\n";
		if (current->pre == NULL) out << "---";
		current = current->pre;
	}
}

//****************************************//
//*****************QUEUES*****************//
//****************************************//
myQueue::myQueue(){ }

int myQueue::getSize() {
	return list.getSize();
}

void myQueue::in(Item *a) {
	list.push_back(a);
}

Item * myQueue::front(){
	return list.getfront();
}

Item * myQueue::out() {
	return list.pop_front();
}

void myQueue::display(ostream &out) {
	Item *current = list.getfront();
	while (current != nullptr) {
		if (current->next == NULL) {
			out << current->val;
		}
		else {
			out << current->val << "<-";
		}
		current = current->next;
	}
}


ostream & operator<<(ostream &out, DLinkedList &list) {

	list.display(out);
	return out;
}
ostream & operator<<(ostream &out, myStack &stack) {
	stack.display(out);
	return out;
}
ostream & operator<<(ostream &out, myQueue &queue) {
	queue.display(out);
	return out;
}

int main() {

	DLinkedList list;
	list.push_front(new Item(1)); //list = 1
	list.push_front(new Item(2)); //2, 1
	list.push_front(new Item(3)); //3, 2, 1
	list.push_back(new Item(4)); //3, 2, 1, 4

	DLinkedList list2(list); //list2 = 3, 2, 1, 4
	DLinkedList list3(list); //list3 = 3, 2, 1, 4
	list3.push_back(new Item(1));

	cout << "test(push front, push back): expected 3, 2, 1, 4... result " << list << endl << endl;

	list.pop_front(); //list = 2,1,4
	list.pop_back(); //2, 1
	list.push_front(new Item(5)); //5, 2, 1
	list.pop_back(); //5, 2

	cout << "test(pop front, pop back): expected 5, 2... result " << list << endl << endl;
	cout << "test(Copy Constructor): expected 3, 2, 1, 4, 1... result " << list3 << endl << endl;
	cout << "test(get front, get back): expected 3 and 4... result " << list2.getfront()->val << " and " << list2.getback()->val << endl << endl;

	Item a(6);
	Item b(7);
	Item c(8);
	Item d(9);
	list.insert(&a, 4); //5, 2, 6
	list.insert(&b, 2); //5, 2, 7, 6
	list.insert(&c, 0); //8, 5, 2, 7, 6
	list.insert(&d, 3); //8, 5, 2, 9, 7, 6

	list.pop_this(&b); //8, 5, 2, 9, 6
	list.pop_at(3); //8, 5, 9, 6

	cout << "test(insert, my pops): expected 8, 5, 9, 6... result " << list << endl << endl;

	list.insertlist(&list2, 1); //8, 3, 2, 1, 4, 5, 9, 6

	cout << "test(insert list): expected 8, 3, 2, 1, 4, 5, 9, 6... result " << list << endl << endl;
	cout << "test(getSize, findindex): expected 8 and 8... result " << list.getSize() << " and " << list.findindex(&a) << endl << endl;

	list.swap(&c, &d); //9, 3, 2, 1, 4, 5, 8, 6

	cout << "test(swap 1): expected 9, 3, 2, 1, 4, 5, 8, 6... result " << list << endl << endl;

	list.pop_front(); //3, 2, 1, 4, 5, 8, 6
	list.pop_front(); //2, 1, 4, 5, 8, 6
	list.pop_front(); //1, 4, 5, 8, 6
	list.pop_front(); //4, 5, 8, 6
	list.insert(&b, 2); //4, 5, 7, 8, 6
	list.swap(&c, &b); //4, 5, 8, 7, 6

	cout << "test(swap 2): expected 4, 5, 8, 7, 6... result " << list << endl << endl;

	Item e(10);
	Item f(4);
	list.insert(&e, 1); //4, 10, 5, 8, 7, 6
	list.insert(&f, 3); //4, 10, 5, 4, 8, 7, 6

	cout << "test(extract min/max): expected 6 and 8... result " << list.extractmin(&f)->val << " and " << list.extractmax(&e)->val << endl << endl;

	cout << list << endl << endl;
	
	return 0;
}