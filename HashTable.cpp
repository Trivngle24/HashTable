#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <cctype>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include "math.h"


#include "HashTable.h"

using std::isalpha;
using std::cout;
using std::endl;
using std::tolower;
using std::size_t;
using Val = std::string;
using std::vector;

int isPrime(int n);

//Create a hash table of capacity defaultCapacity.
HashTable::HashTable() {
	arr = make_unique<LinkedList[]>(defaultCapacity);
	capa = defaultCapacity;
}

//Create a hash table to store n items where n is the constructor’s 
//single int parameter. The capacity of the table should be the 
//smallest prime ≥2n. If n<1, throw a std::invalid_argument 
//(defined in <stdexcept>).
HashTable::HashTable(int c) {
	if (c < 1)  throw std::invalid_argument("ERROR(constructor): parameter<1");
	int twoN = 2 * c;
	while (isPrime(twoN) == 0)
		twoN++;

	arr = make_unique<LinkedList[]>(twoN);
	capa = twoN;

}

//Construct a deep copy of its HashTable reference parameter.
HashTable::HashTable(const HashTable& ht) {
	arr = make_unique<LinkedList[]>(ht.capa);
	for (int i = 0; i<ht.capa; i++)
		arr[i] = ht.arr[i];
	capa = ht.capa;
}

HashTable& HashTable::operator=(const HashTable& ht) {
	if (this == &ht)
		return *this;

	arr = make_unique<LinkedList[]>(ht.capa);
	for (int i = 0; i<ht.capa; i++)
		arr[i] = ht.arr[i];

	capa = ht.capa;
	return *this;
}

//Verify the single string parameter. If the parameter is acceptable 
//and it is not already in the table, add it to the HashTable; 
//return true if the parameter was added (it was not already in the table), 
//return false otherwise (the parameter was already in the table).
bool HashTable::add(const Val& v) {
	auto str = v;
	int i = 0;
	while (isalpha(str[i]))
		i++;
	if (i != str.size())
		throw std::invalid_argument("ERROR(add): invalid string parameter");

	int index = compress(hash(v));
	if (arr[index].add(v)) {
		count++;
		return true;
	}
	//cout << v << " - " << index << endl;
	return false;
}

//Verify the single string parameter. If the parameter 
//is acceptable and it is in the HashTable, remove it; return true 
//if the parameter value was found and removed, return false if the 
//parameter value was not found in the table.
bool HashTable::remove(const Val& v) {
	auto str = v;
	int i = 0;
	while (isalpha(str[i]))
		i++;
	if (i != str.size())
		throw std::invalid_argument("ERROR(remove): invalid string parameter");

	int index = compress(hash(v));
	if (arr[index].remove(v)) {
		count--;
		return true;
	}

	return false;
}

//Verify the single string parameter. If the parameter is 
//acceptable, return true if it is contained in the HashTable, 
//return false otherwise.
bool HashTable::search(const Val& v) {
	auto str = v;
	int i = 0;
	while (isalpha(str[i]))
		i++;
	if (i != str.size())
		throw std::invalid_argument("ERROR(search): invalid string parameter");

	int index = compress(hash(v));
	if (arr[index].search(v))
		return true;
	return false;
}

//Return the number of items stored in the HashTable.
int HashTable::size() const {
	return count;
}

//Return the (int) size of the HashTable’s underlying array.
int HashTable::capacity() const {
	return capa;
}

//Return a vector<string> containing all the entries in this table. 
//Their order can be arbitrary but each element must occur exactly once.
std::vector<Val> HashTable::keys() const {
	vector<Val> str;
	for (int i = 0; i<capa; i++) {		
			vector<Val> str2 = arr[i].get();
			for (int j = 0; j<str2.size(); j++)
				str.push_back(str2[j]);
	}
	return str;
}

//Return the (float) load factor of the HashTable.
float HashTable::loadFactor() const {
	return (float(count) / float(capa));
}

//Return a HashTable containing the set union of this table and 
//its single HashTable reference parameter. The entries in the 
//result table are deep copies of the entries in the original two tables.
HashTable HashTable::setunion(const HashTable& ht) const {

	auto str = ht;
	vector<Val> str2;
	for (int i = 0; i<capa; i++) {
		str2 = arr[i].get();
		for (int j = 0; j<str2.size(); j++)
			str.add(str2[j]);
	}

	return str;
}

//Compute the hash code for its string parameter. See the hash code 
//description for the type of the result. This function does not 
//depend upon any member variables and so is declared static.
//hash = ch0 * 37^n-1 + ch1 * 37^n-2 + ...
std::uint32_t HashTable::hash(const Val & key)
{
	if (key.length() == 0)
		return 0;
	if (key.length() == 1)
		return (int)tolower(key[0]) - 96;

	uint32_t HASH = ((int)tolower(key[0]) - 96) * 37;
	uint32_t ch;

	for (int i = 1; i<key.length() - 1; i++) {
		ch = (int)tolower(key[i]) - 96;
		HASH = (ch + HASH) * 37;
	}

	HASH = HASH + ((int)tolower(key[key.length() - 1]) - 96);

	return HASH;
}

//Given a hash code of type std::uint32_t, compress to the appropriate 
//index for the capacity of this table. Unlike hash, this function refers 
//to a member value of the instance, so it is not static.
std::size_t HashTable::compress(std::uint32_t hash) const {
	return hash % capa; // % totoal array size
}

//Print the table contents on cout. Use any format you wish.
void HashTable::printTable(const std::string& label) const {
	cout << label << endl;
	for (int i = 0; i<capa; i++)
		arr[i].printList();
	cout << endl;
}

int isPrime(int n)
{
	int i, root;
	if (n % 2 == 0 || n % 3 == 0)
		return 0;
	root = sqrt(n);
	for (i = 5; i <= root; i += 6) {
		if (n%i == 0)
			return 0;
	}
	for (i = 7; i <= root; i += 6) {
		if (n%i == 0)
			return 0;
	}
	return 1;
}