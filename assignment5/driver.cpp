#include <iostream>
#include <fstream>
#include "MovieTree.hpp"
#include <sstream>
using namespace std;

int menu() //returns input
{
  string input; //holds user input

  cout<< "======Main Menu====== "<<endl;
  cout<< "1. Find a movie"<<endl;
  cout<< "2. Query movies"<<endl;
  cout<< "3. Print the inventory "<<endl;
  cout<< "4. Average Rating of movies "<<endl;
  cout<< "5. Quit "<<endl;

  getline(cin, input);
  return stoi(input);
}


int main(int argc, char* argv[])
{
  MovieTree M;
  ifstream movieFile;
  movieFile.open(argv[1]); //open first argument




  string value; //for holding each csv
  string line; //for holding entire line
  int count = 1; //helps sort values into correct index

  //store values for each film
  int ranking;
  string title;
  int year;
  float rating;





  if(movieFile.is_open())
  {
    while(getline(movieFile, line))//first parse lines
    {
      //cout<<line;
      int count = 1; //helps sort values into correct index
      stringstream ss(line);
      while(getline(ss, value, ',') && count < 5) //next seperate at comma
      {
        switch(count)
        {
          case 1: //ranking
            ranking = stoi(value);
            break;

          case 2: //title
            title = value;
            break;

          case 3: //year
            year = stoi(value);
            break;

          case 4: //rating
            rating = stof(value);
            M.addMovieNode(ranking, title, year, rating); //add new node for each line
            break;

        }
        count++; //update where to put value
      }
    }
    int input = 0; //for holding menu choice
    string sinput; //for taking inputs in case
    string sinput2;
    while(input != 5)
    {
      input = menu();
      switch(input)
      {
        case 1:
          cout<<"Enter title:"<<endl;
          getline(cin, sinput);
          M.findMovie(sinput);
          break;

        case 2:
          cout<<"Enter minimum rating:"<<endl;
          getline(cin, sinput);
          cout<<"Enter minimum year:"<<endl;
          getline(cin, sinput2);
          M.queryMovies(stof(sinput), stoi(sinput2));
          break;

        case 3:
          M.printMovieInventory();
          break;

        case 4:
          M.averageRating();
          break;

        case 5:
          cout<<"Goodbye!" <<endl;
          return 0;
          break;

      }
    }
  }
  else
    cout<<"Movie file not found."<<endl;
}
