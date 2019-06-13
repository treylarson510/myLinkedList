//Loren Larson CS132
#pragma once
#include <ostream>

using namespace std;
template <class P>
class Node
{
public:
	//constructor----------------------------------------
	Node(P newPayload, Node* newNext)
	{
		payload = newPayload;
		next = newNext;
	}


	~Node()
	{
	}
	//accessor-----------------------------------------------
	P getPayload() const {
		return payload;
	}

	Node * getNext() const {
		return next;
	}
	//mutator-------------------------------------------------
	void setPayload(P newPayload) {
		payload = newPayload;
	}

	void setNext(Node * newNext) {
		next = newNext;
	}
	//overide--------------------------------------------------
	friend ostream & operator<<(ostream & outStream, const Node & node)
	{
		outStream << node.payload;
		return outStream;
	}


private:
	P payload;//stores value for node
	Node *next;//stores pointer for next node

};

