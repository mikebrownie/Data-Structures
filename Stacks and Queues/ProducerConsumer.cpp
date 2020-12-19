/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produces items into the queue)" << endl;
	cout << "2. Consumer (Consumes items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
}


//Constructor--Set queueFront and queueEnd to -1
ProducerConsumer::ProducerConsumer()
{
	queueFront = -1;
	queueEnd = -1;
}


// Return true if the queue is empty, false otherwise
bool ProducerConsumer::isEmpty()
{
	if(queueEnd==-1 || queueFront==-1)
		return true;
	return false;
}


//Return true if the queue is full, false otherwise
bool ProducerConsumer::isFull()
{
	if (queueEnd+queueFront == SIZE-1)
		return true;
	return false;
}


// //If the queue is not full, then add the item to the end of the queue and modify
// queueFront and/or queueEnd if appropriate, else print “Queue full, cannot add new
// item”

void ProducerConsumer::enqueue(string player)
{
	if (!isFull())
	{
		if (queueEnd == SIZE - 1)
		{
			queueEnd = 0;
			queue[queueEnd] = player;
		}
		else
		{
		queueEnd+=1;
		queue[queueEnd] = player;
		if (queueFront == -1)
			++queueFront;
		}
	}
	else
	{
		cout<<"Queue full, cannot add new item"<<endl;
	}
}


// // Remove the first item from the queue if the queue is not empty and modify queueFront
// and/or queueEnd if appropriate. Otherwise print "Queue empty, cannot dequeue an
// item"
void ProducerConsumer::dequeue()
{
	if(isEmpty())
	{
		cout<<"Queue empty, cannot dequeue an item"<<endl;
	}
	else
	{
		if (queueFront == queueEnd)
		{
			queueFront = -1;
			queueEnd = -1;
		}
		else if (queueFront == SIZE - 1)
		{
			queueFront = 0;
		}
		else
			queueFront +=1;
	}
}

//return # items in queue
int ProducerConsumer::queueSize()
{
	if(queueFront == -1)
		return 0;
	else
	{
		if(queueEnd>=queueFront)
			return (queueEnd-queueFront+1);
		if (queueEnd<queueFront)
			return (SIZE + queueEnd - queueFront+1);

	}
}

// If the queue is empty then print “Queue empty, cannot peek” and return an empty string.
//Otherwise, return the frontmost item in the queue
string ProducerConsumer::peek()
{
	if (queueFront ==-1)
	{
		cout<<"Queue empty, cannot peek"<<endl;
		return "";
	}
	else
		return queue[queueFront];
}
