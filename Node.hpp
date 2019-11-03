#pragma once

/*
Node Class that accepts generics
	If V is a class or struct the user must ensure comparison and assignment operators will work for that class or struct.
*/
template <typename K, typename V> class Node {
public:
	K key;
	V value;

	Node(K k, V v) {
		key = k;
		value = v;
	}

	void setKey(K k) {
		key = k;
	}

	void setValue(V v) {
		value = v;
	}

	K getKey() {
		return key;
	}

	V getValue() {
		return value;
	}

	friend bool operator>(Node& n, Node& n2) {
		return n.getValue() > n2.getValue();
	}

	friend bool operator<(Node& n, Node& n2) {
		return n.getValue() < n2.getValue();
	}

	friend std::ostream& operator<<(std::ostream& out, const Node<K, V>& n) {
		out << "{" << n.key << ": " << n.value <<"}";
		return out;
	}
};