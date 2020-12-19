#include "MovieTree.hpp"
#include <iostream>
#include <string> //for string

using namespace std;

//  Constructor: Initialize any member variables of the class to default
MovieTree::MovieTree()
{
  root = NULL;
}


//helper function for desctructor
void deleteTree(MovieNode *node)
{
    if (node == NULL) return;

    /*TODO first delete both subtrees */
    else
    {
      deleteTree(node->leftChild);
      deleteTree(node->rightChild);
      delete node;
    }
    /* TODO then delete the node */

}

//  Destructor: Free all memory that was allocated
MovieTree::~MovieTree()
{
  deleteTree(root); //call recursive function
}




//  This private function is meant to be a helper function. Return a pointer to the node with
// the given title, or nullptr if no such movie exists
MovieNode *find(MovieNode* temp, string title)
{
  if (temp == NULL)
    return nullptr;
  if (temp->title == title)
  {
    return temp;
  }
  else if((temp->title.compare(title)> 0)) //if root is greater than input
  {
    return find(temp->leftChild , title);
  }
  else //if root is less than input
  {
    return find(temp->rightChild, title);
  }
}




//  Print every node in the tree in alphabetical order of titles using the following format
// // for every Movie node (m) in the tree
// cout << "Movie: " << m->title << " " << m->rating << endl;
void printTree(MovieNode* node)
{
  if (node == NULL)
    return;
  else
  {
    printTree(node->leftChild);
    cout << "Movie: " << node->title << " " << node->rating << endl;
    printTree(node->rightChild);
  }
}
void MovieTree::printMovieInventory()
{
  printTree(root);
}


MovieNode* insert(MovieNode* sroot, MovieNode* nn)//helper insert function
{
  if (sroot ==NULL)
    return nn;
  else if(sroot->title.compare(nn->title) > 0) //if root is greater
  {
    sroot->leftChild = insert(sroot->leftChild, nn);
  }
  else //if root is smaller
  {
    sroot->rightChild = insert(sroot->rightChild, nn);
  }
}

//  Add a node to the tree in the correct place based on its title. Every node's left children
// should come before it alphabetically, and every node's right children should come after it
// alphabetically. Hint: you can compare strings with <, >, ==, string::compare() function
// etc. You may assume that no two movies have the same title
void MovieTree::addMovieNode(int ranking, string title, int year, float rating)
{
  MovieNode* nn = new MovieNode(ranking, title, year, rating); //make new node
  root = insert(root, nn);
}


//  Find the movie with the given title, then print out its information:


// If the movie isn't found print the following message instead:
// cout << "Movie not found." << endl;
void MovieTree::findMovie(string title)
{
  MovieNode* node = find(root, title);
  if (node == nullptr)
  {
    cout << "Movie not found." << endl;
    return;
  }
  cout << "Movie Info:" << endl;
  cout << "==================" << endl;
  cout << "Ranking:" << node->ranking << endl;
  cout << "Title  :" << node->title << endl;
  cout << "Year   :" << node->year << endl;
  cout << "rating :" << node->rating << endl;
}


//preOrderPrint helper for query movies
void preOrderTraverse(MovieNode* node, int year, float rating)
{
  if (node == NULL)
        return;

  if(node->year > year && node->rating >= rating) //chech condition
    cout << node->title << "(" << node->year << ") " << node->rating << endl;

  /* then recur on left sutree */
  preOrderTraverse(node->leftChild, year, rating);

  /* now recur on right subtree */
  preOrderTraverse(node->rightChild, year, rating);
}
//  Print all the movies with a rating at least as good as rating that are newer than year in
// the preorder fashion using the following format
//
// // each movie that satisfies the constraints should be printed with
// cout << m->title << "(" << m->year << ") " << m->rating << endl;
void MovieTree::queryMovies(float rating, int year)
{
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  preOrderTraverse(root, year, rating);
}



//helper for average
float sumNodes(MovieNode *node)
{
  if (node == NULL)
        return 0;

    /* sum ratings */
    float sum= node->rating + sumNodes(node->leftChild)+ sumNodes(node->rightChild);
    return sum;
}
int countNodes(MovieNode* node)
{
  if (node == NULL)
        return 0;
  return (1+countNodes(node -> leftChild) + countNodes(node->rightChild));
}
//  Print the average rating for all movies in the tree. If the tree is empty, print 0.0. Ue the
// following format
// cout << "Average rating:" << average << endl;
void MovieTree::averageRating()
{
  if (root == NULL)
    cout << "Average rating:0"<< endl;
  else
  {
    float average = 0;
    int count = 0;
    float sum = sumNodes(root);
    count = countNodes(root);
    average = sum/ count;
    cout << "Average rating:" << average << endl;
  }
}
