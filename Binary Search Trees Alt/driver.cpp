#include "MovieTree.hpp"
#include <iostream>
#include <string> //for string
#include <fstream>
#include <sstream>
using namespace std;

int menu()
{
  string input;
  cout<<"======Main Menu======" <<endl;
  cout<<"1. Print the inventory" <<endl;
  cout<<"2. Delete a movie" <<endl;
  cout<<"3. Quit" <<endl;
  getline(cin,input);
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
            M.addMovie(ranking, title, year, rating); //add new node for each line
            break;

        }
        count++; //update where to put value
      }
    }
    int input = 0; //for holding menu choice
    string sinput; //for taking inputs in case
    while (input != 3)
    {
      input=menu();
      switch(input)
      {
        case 1:
          M.printMovieInventory();
          break;
        case 2:
          cout<<"Enter a movie title:"<<endl;
          getline(cin,sinput);
          M.deleteMovie(sinput);
          break;
        case 3:
          cout<<"Goodbye!" <<endl;
          return 0;
          break;
      }
    }
  }
}
