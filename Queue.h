#pragma once
#include "LinkedList.h"
#include <iostream>

using namespace std;
template <class P>

class Queue : public LinkedList <P>
{
	int numQueues = 0;
public:
	Queue(){
		//cout << "Queue constructor\n";
	}
	~Queue() {
		this->clear();
		//cout << "Queue destructor\n";
	}
	//modifiers
	void enqueue(P newPayload) {
		this->addEnd(newPayload);
		//cout << newPayload << " added to queue, number of objects in queue is: " << this->getNumElements()<<endl;
	}

	void destroy() {
		this->clear();
	}

	P dequeue() {
		return this->removeTop();
	}

	//accessors

	P getTop() const {
		return this->readTop();
	}

	int size() const {
		return this->getNumElements();
	}
};

