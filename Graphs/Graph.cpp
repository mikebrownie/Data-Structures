#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>

Graph::Graph()
{
  std::vector<vertex> vertices;
}

Graph::~Graph()
{
  vertices.clear();
}

void Graph::addVertex(std::string cityName)
{
  vertex newVertex;
  newVertex.name = cityName;
  vertices.push_back(newVertex);
}

void Graph::addEdge(std::string city1, std::string city2, int distance)
{
  //1st find cities
  vertex* v1ptr = findVertex(city1);
  vertex* v2ptr = findVertex(city2);

  //store address and distance in edge
  Edge edge1;
  edge1.v = v2ptr;
  edge1.distance = distance;

  v1ptr->Edges.push_back(edge1);
}




void Graph::displayEdges()
{
  for(int v=0; v<vertices.size(); v++)
  {
    //1st print city and 1st edge
    setAllVerticesUnvisited();
    std::cout<<vertices[v].name<<"-->";
    if(!vertices[v].Edges.empty())
    {
      std::cout<<vertices[v].Edges[0].v->name<<" ("<<vertices[v].Edges[0].distance<<" miles)";
      vertices[v].Edges[0].v->visited = true;

      //Print other edges
      for (int i = 1; i < vertices[v].Edges.size(); ++i)
      {
        if(vertices[v].Edges[i].v->visited == false)
        {
          std::cout<<"***"<<vertices[v].Edges[i].v->name<<" ("<<vertices[v].Edges[i].distance<<" miles)";
          vertices[v].Edges[i].v->visited = true;
        }
      }
    }
      std::cout<<std::endl;
  }
}

void Graph::printDFT()
{
  setAllVerticesUnvisited();

  //traverse through every vertex
  //b/c there can be disconected components
  for(int i = 0; i < vertices.size(); i++)
  {
    if (!vertices[i].visited)
      DFT_traversal(&vertices[i]);
  }
}


void Graph::printBFT()
{
  setAllVerticesUnvisited();

  //traverse through every vertex
  //b/c there can be disconected components
  for(int i = 0; i < vertices.size(); i++)
  {
    if (!vertices[i].visited)
      BFT_traversal(&vertices[i]);
  }
}




void Graph::setAllVerticesUnvisited()
{
  for (int i = 0; i < vertices.size(); i++)
      vertices[i].visited = false;
}



//return vertex once found
vertex* Graph::findVertex(std::string name)
{

  for (int i = 0; i< vertices.size(); i++) //do for all vertices in case of disconnecte components
  {
    if(vertices[i].name == name)
      return &vertices[i];
  }
}


void Graph::BFT_traversal(vertex *v)
{
  //create queue for bfs
  std::queue<vertex> q;

  v->visited = true;
  q.push(*v);

  vertex curr;
  //std::vector<vertex>::size_type i;
  int i = 0;
  while(!q.empty())
  {
    //deque and print vertex
    std::cout<<q.front().name<<std::endl;
    curr = q.front();
    q.pop();

    //get all adjacent vertices from vertex s
    //if not visited, mark visited and enqueue
    for(auto vert:curr.Edges) //NEW AUTO SET DATA & RANGE TRAVERSAL
    {
      if(!(vert.v)->visited)
      {
        (vert.v)->visited = true;
        //std::cout<<v->Edges[i].v->name;
        q.push(*(vert.v));
      }
      i++;
    }
  }
}


// vertex DFS(int v)
// {
//
//     // Call the recursive helper function
//     // to print DFS traversal
//     DFSUtil(v, visited);
// }

void Graph::DFT_traversal(vertex *v)
{
  // Mark the current node as visited and
  // print it
  v->visited = true;
  std::cout << v->name << std::endl;


  // Recur for all the vertices adjacent
  // to this vertex
  for (int i = 0; i < v->Edges.size(); ++i)
  {
      if (!v->Edges[i].v->visited)
          DFT_traversal(v->Edges[i].v);
  }
}
