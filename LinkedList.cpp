#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "LinkedList.h"

//Create an empty list.
LinkedList::LinkedList() {
	head = NULL;
	//cout<<"constructed\n";
	//tail = NULL;
}

//Construct a deep copy of its LinkedList reference parameter.
LinkedList::LinkedList(const LinkedList& ll) {
	Node * list = ll.head;
	while (list) {
		add(list->data);
		list = list->next;
	}
}

//De-allocate any dynamic memory associated with the object. Constant-space.
LinkedList::~LinkedList() {
	Node *list = head;
	while (list) {
		head = head->next;
		delete list;
		list = head;
	}
}


LinkedList& LinkedList::operator=(const LinkedList& ll) {

	if (this == &ll)
		return *this;

	Node *original = head;
	while(original){
		remove(original->data);
		original = original->next;
	}

	Node *list = ll.head;
	while (list) {
		add(list->data);
		list = list->next;		
	}

	return *this;
}

//Add a single string parameter to the list; return true if the 
//string was added, return false if the string was already present in the list
bool LinkedList::add(const Val& v) {
	int Search = search(v);
	if (Search == 1) return false;

	Node *newNode = new Node(v);
	if (count == 0) head = newNode;
	else 
	{
		newNode->next = head;
		head = newNode;
	}
	count++;	
	//cout << "added\n";
	
	return true;

	
}

//Remove its single string parameter from the list; return true if the 
//parameter value was found and removed, return false if the parameter 
//value was not found in the list.
bool LinkedList::remove(const Val& v) {
	if (count == 0)  return false;

	if (count == 1) {
		if (head->data == v) {
			head = NULL;
			return true;
		}
		return false;
	}
	
	Node *prev = head;
	Node *second = head->next;

	if (head->data == v) {
		head = second;
		return true;
	}

	while (second) {
		if (second->data == v) {
			prev->next = second->next;
			return true;
		}
		second = second->next;
	}
	return false;
}

//Return true if its single string parameter is contained in the list, 
//return false otherwise.
bool LinkedList::search(const Val& v) const {
	Node *list = head;
	while (list) {
		if (list->data == v) return true;
		list = list->next;
	}
	return false;
}

//Return true if the list is empty, false otherwise.
bool LinkedList::empty() const {
	if (count == 0)
		return true;
	return false;
}

//Return a vector<string> containing the contents of the list.
std::vector<Val> LinkedList::get() const {
	//std::vector<std::string> str;
	std::vector<Val> str;
	Node *l = head;
	while (l) {
		str.push_back(l->data);
		l = l->next;
		//cout<<" get "<<endl;
	}
	return str;
}

//Print the contents of this list on cout in whatever format you wish.
void LinkedList::printList() const {
	Node *list = head;
	while (list) {
		std::cout << list->data << " ";
		list = list->next;
	}	
	std::cout << std::endl;
}