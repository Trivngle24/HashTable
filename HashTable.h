#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "LinkedList.h"

using std::unique_ptr;
using std::make_unique;
using std::string;

class HashTable {
public:
	HashTable();
	HashTable(int c);
	HashTable(const HashTable& ht);
	~HashTable() = default;
	HashTable& operator=(const HashTable& ht);

	bool add(const Val& v);
	bool remove(const Val& v);
	bool search(const Val& v);

	int size() const;
	int capacity() const;
	std::vector<Val> keys() const;
	float loadFactor() const;

	HashTable setunion(const HashTable& ht) const;

	static std::uint32_t hash(const Val& key);
	std::size_t compress(std::uint32_t hash) const;

	constexpr static int defaultCapacity{ 101 };

	void printTable(const std::string& label) const;

private:
	unique_ptr<LinkedList[]> arr = NULL;
	int count{ 0 };
	int capa{ 0 };

	/*struct item {
		string data;
		item* next;
	};

	item* Table[defaultCapacity];*/

};

#endif
