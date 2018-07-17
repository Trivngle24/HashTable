#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "HashTable.h"

using std::cout;
using std::endl;
using std::sort;
using std::string;
using std::vector;

void printVec(const vector<string>& vec) {
	for (auto s : vec)
		cout << s << " ";
	cout << endl;
}

void linkedListTest() {
	cout << "Start LinkedList tests" << endl;
	auto ll = LinkedList{}; // Default constructor
	ll.add("hello"); // add

	cout << endl << "Test of get (should be \"hello\") ";
	printVec(ll.get());

	cout << "Test of empty (should be 0) " << ll.empty() << endl;

	cout << "Test of search (should be 1) " << ll.search("hello") << endl;

	auto ll2 = ll; // Test of copy constructor

	cout << endl << "Test of remove (should be 1) " << ll.remove("hello") << endl;

	auto ll3 = LinkedList{};
	ll3.add("goodbye");
	ll3 = ll2; // Test of copy assignment

	auto items = ll3.get();
	cout << endl << "Test of result of copy assignment (should be \"hello\") ";
	printVec(ll3.get());

	cout << endl << "Test of printList (whatever format you use)" << endl;
	ll.printList();

	cout << endl << "End LinkedList tests" << endl << endl;
}

void hashTableTest()
{
	cout << "Start HashTable tests" << endl;

	cout << "Default capacity " << HashTable::defaultCapacity << endl;

	HashTable ht0{}; // Default constructor; also (implied) destructor
	cout << "Default table size: " << ht0.size() << ", capacity: " << ht0.capacity() << endl; // size and capacity
	HashTable ht1{ 9 }; // Constructor specifying number of items
	ht1.add("bat"); // add
	ht1.add("cat");
	ht1.add("C12");
	ht1.add("rhinoceros");
	ht1.add("ocelot");
	ht1.add("elephant");
	ht1.add("hippopotamus");
	ht1.add("giraffe");
	ht1.add("camel");
	ht1.add("lion");
	ht1.add("panther");
	ht1.add("bear");
	ht1.add("wolf");

	ht1.remove("ocelot");

	cout << "table size after adding: " << ht1.size() << endl;

	cout << "Load factor (should be around 63%): " << ht1.loadFactor() << endl; // loadFactor

																				// Test search
	cout << endl << "Search examples" << endl;
	string test1 = "frog";
	string test2 = "camel";
	cout << test1 << " (should be 0): " << ht1.search(test1) << endl;
	cout << test2 << " (should be 1): " << ht1.search(test2) << endl;

	// Test copy constructor and remove
	HashTable ht2{ ht1 };
	ht2.remove("ocelot");
	ht2.remove("camel");
	ht2.remove("rhinoceros");

	cout << endl;
	ht2.printTable("Test of printTable---whatever your output is"); // printTable

	vector<string> keys = ht2.keys(); // keys

	HashTable ht3{};
	ht3 = ht1; // Copy assignment

			   // Test set union
	ht2.add("kraken");
	HashTable un = ht1.setunion(ht2);
	vector<string> unionKeys = un.keys();
	sort(unionKeys.begin(), unionKeys.end());
	cout << endl << "Set union example. Result should be:" << endl;
	cout << "bat bear camel cat elephant giraffe hippopotamus kraken lion ocelot panther rhinoceros wolf" << endl;
	cout << "Result was:" << endl;
	printVec(unionKeys);

	cout << endl << "Hash of \"Hello\" (should be 15263440): " << HashTable::hash("Hello") << endl;

	cout << endl << "Compress of 15263440 for ht1 (should be 18) " << ht1.compress(std::uint32_t(15263440U)) << endl;

	cout << endl << "End HashTable tests" << endl;
}

int main()
{
	HashTable ht1{ 5 }; // Constructor specifying number of items
	ht1.add("bat"); // add

	try {
		ht1.add("c11");
	}

	catch (std::invalid_argument& oor){
		cout << oor.what() << endl;
	}

	int index = ht1.hash("cat");
	cout << "index = " << index << endl;

	int index2 = ht1.hash("CAT");
	cout << "index2 = " << index2 << endl;






	//linkedListTest();
	//hashTableTest();
	//system("pause");
	return 0;
}
