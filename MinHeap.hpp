#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Node.hpp"

/*
Implementation of a MinHeap using generics
*/
template <typename K, typename V> class MinHeap {
public:
	std::vector<Node<K, V>> myHeap;

	MinHeap() = default;

	//Return parent index of myHeap[i]
	int getParent(int i) {
		return (i - 1) / 2;
	}

	//Return left child index of myHeap[i]
	int getLeft(int i){
		return (2 * i) + 1;
	}

	//Return right child index of myHeap[i]
	int getRight(int i) {
		return (2 * i) + 2;
	}

	size_t size() {
		return myHeap.size();
	}

	void swap(int a, int b) {
		Node<K,V> temp = myHeap[a];
		myHeap[a] = myHeap[b];
		myHeap[b] = temp;
	}

	void heapifyDown(int i) {
		int left = getLeft(i);
		int right = getRight(i);
		int smallest = i;

		if (left < size() && myHeap[left] < myHeap[smallest])
			smallest = left;

		if (right < size() && myHeap[right] < myHeap[smallest]) 
			smallest = right;

		if (smallest != i) {
			swap(i, smallest);
			heapifyDown(smallest);
		}
	}

	void heapifyUp(int i) {
		if (i && myHeap[getParent(i)] > myHeap[i]) { //Checks that i != 0 and that node at i and its parent do not violate heap
			swap(i, getParent(i));
			heapifyUp(getParent(i));
		}
	}

	void push(Node<K,V> n) {
		myHeap.push_back(n);
		int index = size() - 1;
		heapifyUp(index);
	}

	void pop() {
		try {
			if (size() == 0) 
				throw std::out_of_range("MinHeap: Index out of range (Heap Underflow)");
			
			myHeap[0] = myHeap.back();
			myHeap.pop_back();
			heapifyDown(0);
		}
		catch (const std::out_of_range& oor) {
			std::cout << oor.what() << std::endl;
		}
	}

	//Removes node at index i
	void removeIndex(int i) {
		try {
			if (size() == 0)
				throw std::out_of_range("MinHeap: Index out of range (Heap Underflow)");
	
			myHeap[i] = myHeap.back();
			myHeap.pop_back();
			heapifyDown(i);
		}
		catch (const std::out_of_range& oor) {
			std::cout << oor.what() << std::endl;
		}
	}

	/*Removes Node with Key k
		Assumes unique keys 
	*/
	void removeKey(K k) {
		try {
			if (size() == 0)
				throw std::out_of_range("MinHeap: Index out of range (Heap Underflow)");
			int i = findIndexOf(k);
			myHeap[i] = myHeap.back();
			myHeap.pop_back();
			heapifyDown(i);
		}
		catch (const std::out_of_range& oor) {
			std::cout << oor.what() << std::endl;
		}

	}
	
	int findIndexOf(K k) {
		for (size_t i = 0; i < size(); ++i) {
			if (myHeap[i].getKey() == k)
				return i;
		}
		return -1;
	}

	Node<K,V> getNode(int i) {
		return myHeap[i];
	}

	V getValueOf(K k) {
		return myHeap[findIndexOf(k)].getValue();
	}
	
	friend std::ostream& operator<<(std::ostream& out, const MinHeap<K, V>& mh) {
		for (size_t i = 0; i < mh.myHeap.size(); ++i)
			out << mh.myHeap[i] << " ";
		return out;
	}
};