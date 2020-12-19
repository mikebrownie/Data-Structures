#include "MovieTree.hpp"
#include <iostream>
#include <string> //for string

using namespace std;
TreeNode* createNode(char c)
{
    TreeNode* newNode = new TreeNode;
    newNode->titleChar = c;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}


//  Constructor: Initialize any member variables of the class to default
MovieTree::MovieTree()
{
  root = NULL;
}

void deleteList(LLMovieNode* node)
{
  LLMovieNode *next =NULL;
  while (node != NULL)
  {
    next = node->next;
    delete node;
    node = next;
  }
}

//helper function for desctructor
void deleteTree(TreeNode *node)
{
    if (node == NULL) return;

    /*TODO first delete both subtrees */
    else
    {
      deleteTree(node->leftChild);
      deleteTree(node->rightChild);
      deleteList(node->head);
      delete node;
    }
}

//  Destructor: Free all memory that was allocated
MovieTree::~MovieTree()
{
  deleteTree(root); //call recursive function
}

//helper func for printMovieInventory
void printTree(TreeNode* node)
{
  if (node == NULL)
    return;
  else
  {
    printTree(node->leftChild); //far left to start early alphabet

    cout << "Movies starting with letter: " <<node->titleChar<<endl;

    LLMovieNode *temp = node->head; //tem to traverse linked list
    while(temp != NULL)
    {
      cout << " >> " << temp->title << " " << temp->rating << endl;
      temp = temp->next;
    }
    printTree(node->rightChild); //finish with rightmost, end of alphabet
  }
}

void MovieTree::printMovieInventory()
{
  printTree(root);
}



TreeNode* find(TreeNode* currNode, char data){
    if(currNode == NULL)
        return nullptr;

    if(currNode->titleChar == data)
        return currNode;

    if(currNode->titleChar > data)
        return find(currNode->leftChild, data);

    return find(currNode->rightChild, data);
}

//helper function for adding nodes
TreeNode* addNode(TreeNode* currNode, char c)
{
    if(currNode == NULL){
        return createNode(c);
    }
    else if(currNode->titleChar < c){
        currNode->rightChild = addNode(currNode->rightChild, c);
    }
    else if(currNode->titleChar > c){
        currNode->leftChild = addNode(currNode->leftChild, c);
    }
    return currNode;
}


void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
  char titleChar = title[0]; //get first letter
  TreeNode* tempMT = find(root, titleChar);

  LLMovieNode* nn = new LLMovieNode(ranking, title, year, rating); //new node
  if (root == NULL) //for empty
  {
    root = createNode(titleChar);
    root->head = nn;
    return;
  }
  if (tempMT == nullptr) //if not yet created
  {
    TreeNode* newTree = addNode(root, titleChar);
    tempMT = find(root, titleChar);
  }
  if (tempMT != nullptr)
  {
    LLMovieNode* temp = tempMT->head; // temp = head of linked list
    if (temp == NULL)
    {
      tempMT->head = nn;
      return;
    }
    LLMovieNode* prev = NULL; //value before temp

    while(temp != NULL)
    {
      if(temp->title.compare(title) > 0) //if title in list is later in alphabet than given title
      {
        if(temp == tempMT->head) //if goes before head, make into new head
        {
          nn->next = temp;
          tempMT->head = nn;
          return;
        }
        else //if in middle, insert
        {
          prev->next = nn;
          nn->next = temp;
          return;
        }
      }
      if(temp->next == NULL) //if lesser value not found
      {
        temp->next = nn;
        return;
      }
      prev = temp; //update prev and curr
      temp = temp->next;
    }
  }
}




TreeNode* getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

TreeNode* deleteNode(TreeNode* currNode, char titleChar)
{
    if(currNode == NULL)
    {
      return NULL;
    }
    else if(titleChar < currNode->titleChar)
    {
      currNode->leftChild = deleteNode(currNode->leftChild, titleChar);
    }
    else if(titleChar > currNode->titleChar)
    {
      currNode->rightChild = deleteNode(currNode->rightChild, titleChar);
    }
    // We found the node with the value
    else
    {
      //TODO Case : No child
      if(currNode->leftChild == NULL && currNode->rightChild == NULL)
      {
        delete currNode;
        currNode = NULL;
      }
      //TODO Case : Only right child
      else if(currNode->leftChild == NULL)
      {
        TreeNode* delNode = currNode;
        currNode = currNode->rightChild;
        delete delNode;
      }
      //TODO Case : Only leftChild child
      else if(currNode->rightChild == NULL)
      {
        TreeNode* delNode = currNode;
        currNode = currNode->leftChild;
        delete delNode;
      }
      //TODO Case: Both leftChild and right child
      else
      {
        TreeNode* min = getMinValueNode(currNode->rightChild); //can go right or leftChild
        currNode->titleChar = min->titleChar;
        currNode->head = min->head;
        currNode->rightChild = deleteNode(currNode->rightChild, min->titleChar);
      }
      return currNode;
    }
}



void MovieTree::deleteMovie(string title)
{
  char titleChar = title[0]; //get first letter
  TreeNode* charNode = find(root, titleChar); //find char node

  if (charNode == nullptr)
    cout << "Movie: "<<title<<" not found, cannot delete." <<endl;
  else
  {
    LLMovieNode* temp = charNode->head; //make temp to traverse list
    LLMovieNode* prev = NULL;
    while(temp != NULL)
    {
      if(temp->title == title) //if title in list matches given title
      {
        if (prev != NULL) //if not first
          prev->next = temp->next;
        else //for first in list
          charNode->head = temp->next;
        delete temp;
        temp = NULL;
      }
      else
      {
        prev = temp; //update prev and curr
        temp = temp->next;
      }
    }
    if (charNode->head == NULL)
    {
      root = deleteNode(root, charNode->titleChar);
    }
  }
}
