#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>
#include <string>
#include <vector>

using Val = std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::string;
using std::move;
using std::endl;
using std::cout;
// Define class Node here
class Node {
public:
	Node(const Val& v) : data{v}
	{
	}
	Node* next = NULL;
	//const Val& data;
	string data = "";
	
private:
	
};

/*typedef struct _node {
	Val& data;
	struct _node * next;
} Node;*/


class LinkedList {
public:
	LinkedList();
	LinkedList(const LinkedList& ll);
	~LinkedList();

	LinkedList& operator=(const LinkedList& ll);

	bool add(const Val& v);
	bool remove(const Val& v);

	bool search(const Val& v) const;
	bool empty() const;

	std::vector<Val> get() const;

	void printList() const;

private:
	//Node *tail;	
	Node *head = NULL;
	int count{ 0 };
};

#endif
