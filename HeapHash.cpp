#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <sstream>
#include <fstream>
#include <utility>
#include <string>
#include "MinHeap.hpp"

using namespace std;

/*
A Hash map that stores into MinHeaps instead of linked lists. 
	t1 must be a hashable type by std::hash<>
*/
template<typename t1, typename t2> class HeapHash {
public:
	vector<MinHeap<t1, t2>> myMap;

	//Disables default constructor so that myMap must always be initialized before use
	HeapHash() = delete;

	HeapHash(int size) {
		myMap.resize(size);
	}

	//Returns which index a key should be stored in. 
	size_t createHash(t1 key) {
		return hash<t1>{}(key) % myMap.size();
	}


	void ReadIn(const char* filename){
		ifstream file{ filename };
		string line;
		if (!file) {
			cerr << "Unable to open file" << endl;
			exit(1);
		}
	    t1 key;
		t2 val;
		while (getline(file, line)) {
			stringstream ss(line);
			while (ss >> key && ss >> val) {
				Node<t1,t2> n(key, val);
				myMap[createHash(n.getKey())].push(n);
			}
		}
		file.close();
	
	}

	void add(Node<t1, t2> n) {
		myMap[createHash(n.getKey())].push(n);
	}

	t2 getValue(t1 k) {
		return myMap[createHash(k)].getValueOf(k);
	}

	friend std::ostream& operator<<(std::ostream& out, const HeapHash<t1, t2>& hh) {
		for (size_t i = 0; i < hh.myMap.size(); ++i)
			out << hh.myMap[i] << std::endl;
		return out;
	}

};

int main() {
	HeapHash<string, int> hh(1);
	hh.ReadIn("ClassMarks.txt");
	cout<<hh;
	return 0;
}