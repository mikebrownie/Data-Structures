#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "PriorityQueue.hpp"

int menu()
{
  std::string input;
  std::cout << "============Main Menu============" << std::endl;
  std::cout << "1. Get group information from file" << std::endl;
  std::cout << "2. Add a group to Priority Queue" << std::endl;
  std::cout << "3. Show next group in the queue" << std::endl;
  std::cout << "4. Serve Next group" << std::endl;
  std::cout << "5. Serve Entire Queue" << std::endl;
  std::cout << "6. Quit" << std::endl;
  getline(std::cin, input);
  return std::stoi(input);
}


int main(int argc, char* argv[])
{
  PriorityQueue* pQ = new PriorityQueue(std::stoi(argv[1])); //argv[1] = max queue size

  int input = 0; //for holding menu choice
  std::string sinput; //for taking inputs in case
  std::string sinput2;
  std::string sinput3;

  int totalCookTime = 0; //case4

  while (input != 6) //6 = quit
  {
    input=menu();
    switch(input)
    {
      case 1: //get group information from file
      {
        std::cout<<"Enter filename:"<<std::endl;
        getline(std::cin, sinput);
        std::ifstream readFile;
        readFile.open(sinput);
        std::string line;

        //Information to be extracted:
        std::string groupName;
        int groupSize;
        int cookingTime;

        std::string value; //first above info goes into this

        while(getline(readFile, line))//first parse lines
        {
          //cout<<line;
          int count = 1; //helps sort values into correct index
          std::stringstream ss(line);
          while(getline(ss, value, ' ') && count < 4) //next seperate at space
          {
            switch(count) //store info based on order
            {
              case 1:
                groupName = value;
                break;
              case 2:
                groupSize = std::stoi(value);
                break;
              case 3:
                cookingTime = std::stoi(value);
                break;
            }
          }
          pQ->enqueue(groupName, groupSize, cookingTime); //enque after gathering info
        }
        break;
      }
      case 2: //add group
        std::cout << "Enter Group Name:" << std::endl;
        getline(std::cin, sinput);
        std::cout << "Enter Group Size:" << std::endl;
        getline(std::cin,sinput2);
        std::cout << "Enter Estimated Cooking Time:" << std::endl;
        getline(std::cin,sinput3);
        pQ->enqueue(sinput, std::stoi(sinput2), std::stoi(sinput3));
        break;


      case 3:
        if(!pQ->isEmpty())
        {
          std::cout << "Group Name: " << pQ->peek().groupName << std::endl;
          std::cout << "Group Size: " << pQ->peek().groupSize << std::endl;
          std::cout << "Group Time: "<< pQ->peek().cookingTime
          << std::endl;
        }
        else
          std::cout<<"Heap empty, nothing to peek"<<std::endl;
        break;


      case 4: //remove group, update cooktime
        /* For a priority queue object myQueue
        int totalCookTime = totalCookTime of prioritized groups that
        were served previously + cook time of the current group
        */
        if(!pQ->isFull())
        {
          totalCookTime += pQ->peek().cookingTime;
          std::cout << "Group Name: " << pQ->peek().groupName
          << " - Total Cook Time for the Group: " << totalCookTime << std::endl;
          pQ->dequeue();
        }
        else
          std::cout<<"Heap empty, nothing to peek"<<std::endl;
        break;


      case 5: //serve entire queue
        while(!pQ->isEmpty())
        {
          totalCookTime += pQ->peek().cookingTime;
          std::cout << "Group Name: " << pQ->peek().groupName
          << " - Total Cook Time for the Group: " << totalCookTime << std::endl;
          pQ->dequeue();
        }
        break;
      case 6:
        std::cout<<"Goodbye!"<<std::endl;
        break;
}
}
}
