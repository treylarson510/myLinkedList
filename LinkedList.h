#pragma once
#include "Node.h"
#include "pch.h"
#define NDEBUG
#include <cassert>
#include <exception> 
#include <iostream>
#include <ostream>

using namespace std;
template <class P>

class LinkedList
{
//nt numLists = 0;
public:
	//constructor--------------------------------------------------------------------
	LinkedList() {
		top = nullptr;
		end = nullptr;
		numNodes = 0;
		//cout << "Linked List Constructor\n";
	}
	//destructor---------------------------------------------------------------------
	virtual ~LinkedList() {
		clear();
		//cout << "Linked List destructor, active elements: "<<numNodes<<endl;

	}


	//clears list
	void clear() {
		while (numNodes >0) {//returns memory
			removeTop();
		}
	}

	//adding methods-----------------------------------------------------------------
	void addTop(P newPayload) {
		try {
			Node<P> *newNode = new Node <P>(newPayload, nullptr);//temporary node used

			if (end == nullptr) {
				top = newNode; ++numNodes;
				end = newNode;
				}
			else {
				top = new Node <P>(newPayload, top); ++numNodes;
			}
		}
		catch (exception &e)
		{
			cerr << "Caught: " << e.what() << endl;
			cerr << "Type: " << typeid(e).name() << endl;
		}
	}

	void addEnd(P newPayload) {
		try {
			//create new node
			Node<P> *newNode = new Node <P>(newPayload, nullptr);

			if (numNodes == 0) {//if there arent any nodes already in the queue
				top = newNode; end = newNode; ++numNodes;//sets top and end to the same node
			}
			else {//otherwise it will add the node to the end, not effecting top and moving end to the next end node
				end->setNext(newNode); end = newNode; ++numNodes;

			}
		}
		catch (exception &e)
		{
			cerr << "Caught: " << e.what() << endl;
			cerr << "Type: " << typeid(e).name() << endl;
		}

	}

	//will add a new element at index given
	//0 to numNodes-1
	//adding at 0 index will add at the top
	//adding at numNodes index will add at the end
	void addAtIndex(int index, P newPayload) {
		assert(index >= 0);
		assert(index <= numNodes);
		if (index < 0|| index > numNodes){
			throw runtime_error("Illegal  addAtIndex()");
		}
		if (index == 0) {//if user wants to add at index 0
			Node<P> *newNode = new Node <P>(newPayload, nullptr);//temporary node used

			if (end == nullptr) {
				top = newNode; ++numNodes;
				end = newNode;
			}
			else {
				top = new Node <P>(newPayload, top); ++numNodes;
			}
		}
		else if (index == numNodes) {//if user wants to add after the last element
			//create new node
			Node<P> *newNode = new Node <P>(newPayload, nullptr);

			if (numNodes == 0) {//if there arent any nodes already in the queue
				top = newNode; end = newNode; ++numNodes;//sets top and end to the same node
			}
			else {//otherwise it will add the node to the end, not effecting top and moving end to the next end node
				end->setNext(newNode); end = newNode; ++numNodes;

			}
		}
		else {
			try {
				//pointer to travers list to desired index, starts at the top
				Node <P> *curr = top;
				Node <P>*next = new Node<P>(newPayload, nullptr);
				for (int i = 0; i < index-1; i++) {
					curr = curr->getNext();
				}
				//create new node
				next->setNext(curr->getNext());
				curr->setNext(next);	numNodes++;
				//curr->setPayload(newPayload);

			}
			catch (exception &e)
			{
				cerr << "Caught: " << e.what() << endl;
				cerr << "Type: " << typeid(e).name() << endl;
			}
		}
	}

	//removing methods---------------------------------------------------------------------
	P removeTop() {
		assert(top != nullptr);
		if (top == nullptr) {
			throw runtime_error("Illegal pop()");
		}
		P returnVal = top->getPayload();
		Node<P> *temp = top->getNext();
		delete top;	numNodes--;
		top = temp;
		if (numNodes == 0) {
			assert(top == nullptr);
				end = nullptr;
		}
		return returnVal;
	}

	P removeEnd() {
		assert(end != nullptr);
		if (end == nullptr) {
			throw runtime_error("Illegal pop()");
		}
		Node <P> *temp = top;

		while (temp->getNext() !=end) {
			temp = temp->getNext();
		}
		P returnVal = end->getPayload();
		delete (end);	numNodes--;
		end = temp;
		end->setNext(nullptr);
		return returnVal;
	}

	//will remove element at index given
	//0 to numNodes-1
	//remove at 0 index will removeTop
	//removing at numNodes -1 will remove the end
	P removeAtIndex(int index) {
		assert(index >= 0);
		assert(index < numNodes);
		P returnVal;
		if (index < 0 || index >= numNodes) {
			throw runtime_error("Illegal  removeAtIndex()");
		}
		if (index == 0) {//if user wants to remove index 0
			returnVal = removeTop();
		}
		else if (index == numNodes-1) {//if user wants to remove the last index
			returnVal=removeEnd();
		}
		else {
				//pointer to travers list to desired index, starts at the top, destroy will be the deleted index
				Node <P> *destroy, *curr = top;
				for (int i = 0; i < index-1; i++) {
					curr = curr->getNext();
				}
				destroy = curr->getNext();
				returnVal = destroy->getPayload();
				curr->setNext(destroy->getNext());
				delete(destroy); numNodes--;
		}
		return returnVal;
	}
	//accessors-----------------------------------------------------------------------------
	P readTop() const {
		/*assert(top != nullptr);
		if (top == nullptr) {
			throw runtime_error("Illegal readTop()");
		}*/
		return top->getPayload();
	}

	P readEnd() const {
		/*asser(end != nullptr);
		if (end == nullptr)
			throw runtime_error("Illegal readEnd()");*/
		return end->getPayload;
	}
	//Number of nodes in the list
	int getNumElements() const {
		return numNodes;
	}
	//overloads---------------------------------------------------------------------------------


	//== operator overloader
	bool operator == (const LinkedList &rhs)const {
		//stores return value
		bool returnval = false;
		//if the number of nodes are the same
		if (this == &rhs) {
			//creates two nodes to traverse the stacks	
			returnval = true;
		}
		else 	//if the stacks are the same stack
			if (this->numNodes == rhs.getNumElements()) {
				returnval = true;
				Node <P> *left = this->top;
				Node <P> *right = rhs.top;
				while (left->getNext() != nullptr &&returnval == true) {

					if (left->getPayload() != right->getPayload())
						returnval = false;
					left = left->getNext();	right = right->getNext();
				}
			}
		return returnval;
	}

	//cout operator overloader
	friend ostream& operator <<(ostream& outStream, const LinkedList& list) {
		list.printHelper2(outStream, list.top);
		return outStream;
	}

private:
	Node <P> *top;
	Node <P> *end;
	 int numNodes;
	void copy(const Node<P> *from) {
		while(from != nullptr) {
			addEnd(from->getPayload());
			from = from->getNext();
		}
	}

	//recursive function for reverse print
	void printHelper2(ostream& outStream, Node <P>*curr)const {
		while (curr != nullptr) {
			outStream << *curr << " ";
			curr = curr->getNext();
		}
	}


};
