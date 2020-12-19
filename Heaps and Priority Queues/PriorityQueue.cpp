#include "PriorityQueue.hpp"
#include <iostream>
//Purpose: perform all operations necessary to instantiate a class object
PriorityQueue::PriorityQueue(int queueSize)
{
  this->maxQueueSize = queueSize;
  this->currentQueueSize = 0;
  priorityQueue = new GroupNode[queueSize];
}


void swap(struct GroupNode *a, struct GroupNode *b)
{
  struct GroupNode temp = *a;
  *a = *b;
  *b = temp;
}


/*
Returns the left child of a node.
*/
int leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int rightChild(int index)
{
  return ((2*index) + 2);
}


int parent(int index)//returns parent of child
{
  return (index-1)/2;
}


// Purpose: free all resources that the object has acquired
PriorityQueue::~PriorityQueue()
{

 delete [] priorityQueue;
  priorityQueue = NULL;
}




// Purpose: enqueue new group into priority queue; call other
//
void PriorityQueue::enqueue (std::string _groupName, int _groupSize, int _cookingTime)
{
  //create new group node
  GroupNode newGroup;
  newGroup.groupName = _groupName;
  newGroup.groupSize = _groupSize;
  newGroup.cookingTime = _cookingTime;

  //check if full
  if (isFull())//if full
  {
    std::cout<<"Heap full, cannot enqueue"<<std::endl;
  }
  else
  {
    priorityQueue[currentQueueSize] = newGroup; //add to end of array
    repairUpward(currentQueueSize); //repair queue
    currentQueueSize++; //increment quesize

  }
}




//Purpose: remove the group (allocate the table) at the front of the priority queue from
void PriorityQueue::dequeue()
{
  if(isEmpty())
    std::cout<<"Heap empty, cannot dequeue"<<std::endl;
  else
  {
    currentQueueSize--;
    priorityQueue[0] = priorityQueue[currentQueueSize];
    repairDownward(0);
  }
}





// return: groupID of the group at the front of the priority queue
GroupNode PriorityQueue::peek()
{
  return priorityQueue[0];
}




//return: true if queue is full, false otherwise
bool PriorityQueue::isFull()
{
  if (currentQueueSize == maxQueueSize)
    return true;
  return false;
}



// return: true if queue is empty, false otherwise
bool PriorityQueue::isEmpty()
{
  if (currentQueueSize == 0)
    return true;
  return false;
}


//private:
//Purpose: maintain heap properties by swapping node with parent if necessary

// Prioritize smaller groups over larger groups. For any two groups of the
// same size, you prioritize customers whose meals are faster to cook.

void PriorityQueue::repairUpward(int i)
{
  if (i != 0)
  {
    int p=parent(i);
    if (priorityQueue[p].cookingTime > priorityQueue[i].cookingTime && priorityQueue[i].groupSize == priorityQueue[p].groupSize)
    {
      swap(&priorityQueue[p], &priorityQueue[i]);
      repairUpward(p);
    }
    if(priorityQueue[p].groupSize > priorityQueue[i].groupSize)
    {
      swap(&priorityQueue[p], &priorityQueue[i]);
      repairUpward(p);
    }
  }
}



// Purpose: maintain heap properties by swapping node with child if necessary
void PriorityQueue::repairDownward(int nodeIndex)
{
  for (int i = nodeIndex; i < (currentQueueSize+1)/2; i++) //moving backward through queue
  {
    int leftc = leftChild(i);
    int rightc = rightChild(i);

    if(leftc < currentQueueSize && priorityQueue[i].groupSize >= priorityQueue[leftc].groupSize)
    {
      if (priorityQueue[i].groupSize == priorityQueue[leftc].groupSize)
      {
        if (priorityQueue[i].cookingTime > priorityQueue[leftc].cookingTime)
          swap(&priorityQueue[leftc], &priorityQueue[i]);
      }
      else
        swap(&priorityQueue[leftc], &priorityQueue[i]);
    }
    if(rightc < currentQueueSize && priorityQueue[i].groupSize >= priorityQueue[rightc].groupSize)
    {
      if (priorityQueue[i].groupSize == priorityQueue[rightc].groupSize)
      {
        if (priorityQueue[i].cookingTime > priorityQueue[rightc].cookingTime)
          swap(&priorityQueue[rightc], &priorityQueue[i]);
      }
      else
        swap(&priorityQueue[rightc], &priorityQueue[i]);
    }

  }
}
