/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"
using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  Country* head=NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
  if(head == NULL)
    return true;
  return false;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
  if(previous==NULL)
  {
    cout << "adding: " << countryName << " (HEAD)" << endl;
    Country *newNode = new Country;
    newNode->name = countryName;
    newNode->next = head;
    head = newNode;
  }
  else
  {
    cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;

    Country *newCountry = new Country;
    newCountry->name = countryName;

    Country *temp = previous->next;
    previous->next = newCountry;
    newCountry->next = temp;

  }
}

/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
 //https://stackoverflow.com/questions/15603009/deleting-node-in-linked-list-c
 //^Used to help conceptual understanding of linked list deletion
 void CountryNetwork::deleteCountry(string countryName)
 {
   Country *current = head;
   Country *next = current->next;
   bool deleted = false; //track whether or not deleted

   if(current->name == countryName) //checking 1st index
   {
     delete current;
     current = next;
     head = next; //reset head of list
     deleted = true;
   }
   while(next != NULL) //traverse until data is found
   {
     if (next->name == countryName)
     {
       current->next=next->next;
       delete next;
       deleted=true;
     }
     else
       current = next;
     next = next->next;
   }
   if (!deleted)
     cout<<"Country does not exist."<<endl;
 }


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
  deleteEntireNetwork();
  insertCountry(NULL, "United States");
  Country *previous = head;
  insertCountry(previous, "Canada");
  insertCountry(previous->next, "Brazil");
  insertCountry(previous->next->next, "India");
  insertCountry(previous->next->next->next, "China");
  insertCountry(previous->next->next->next->next, "Australia");
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
  Country* current = head;
  bool found = false;
  while(current != NULL)
  {
    if (current->name == countryName)
    {
      found = true;
      break;
    }
    current = current->next;
  }

  if(!found)
    return NULL;
  else
    return current;
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
 void CountryNetwork::deleteEntireNetwork()
 {
   if(head == NULL)
     return;
   else
   {
     Country* current = head;
     while(current != NULL)
     {
       cout << "deleting: " << current->name << endl;
       delete current;

       if (current->next != NULL)
         current = current->next;

       else
        break;
     }
     cout << "Deleted network" << endl;
     head = NULL;
   }
 }


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  Country *current= head;
  while(current != NULL)
  {
    current->message = message;
    current->numberMessages++;
    cout << current->name << " [# messages received: " <<
    current->numberMessages << "] received: " << current->message << endl;
    if(current->name == receiver)
      break;
    current=current->next;
  }
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
  cout<<"== CURRENT PATH =="<<endl;
  Country *current = head;
  if (current == NULL)
  {
    cout<<"nothing in path"<<endl<<"===\n"<<endl;
    return;
  }
  else
  {
    while (current != NULL)
    {
      cout<< current->name <<" -> ";
      current = current->next;
    }
    cout<<"NULL"<<endl;
    cout<<"===\n"<<endl;
  }
}


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
 //Method: https://www.geeksforgeeks.org/reverse-a-linked-list/

void CountryNetwork::reverseEntireNetwork()
{
  Country *prev = NULL; //will be pointed to by current after reversing
  Country *current = head; //start at beginning of list
  Country *next = NULL; //for saving pointer

  while(current != NULL)
  {
    next = current->next; //save pointer to next value
    current->next = prev; //reverse pointer of current
    prev=current; // increment previous by 1
    current=next; //increment current value by 1
  }
  head = prev; //make the head the last node
}












/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/


#include "CountryNetwork.hpp"
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
  CountryNetwork* C = new CountryNetwork(); //TODO INSTANTIATE CLASS

  string input = "0";
  while(stoi(input) != 8)
  {
    displayMenu();
    getline(cin, input);

    switch(stoi(input))
    {
      case 1:
      {
        C->loadDefaultSetup();
        C->printPath();
        break;
      }
      case 2:
      {
        C->printPath();
        break;
      }
      case 3:
      {
        string country, msg;
        cout<<"Enter name of the country to receive the message:"<<endl;
        getline(cin, country);
        cout<<"Enter the message to send:\n"<<endl;
        getline(cin, msg);
        C->transmitMsg(country, msg);
        cout<<endl;
        break;
      }
      case 4: //TODO FINISH
      {
        string prev, country;
        cout<<"Enter a new country name:"<<endl;
        getline(cin, country);
        Country *ptr = NULL;

        cout<<"Enter the previous country name (or First):"<<endl;
        getline(cin,prev);

        ptr = C->searchNetwork(prev);


        while (ptr == NULL)
        {
          if (prev == "First")
          {
            break;
          }
          cout << "INVALID country...Please enter a VALID previous country name:" << endl;
          getline(cin,prev);
          ptr = C->searchNetwork(prev);
        }
        C->insertCountry(ptr, country);
        C->printPath();
        break;
      }
      case 5:
      {
        string country;
        cout<<"Enter a country name:"<<endl;
        getline(cin, country);
        C->deleteCountry(country);
        C->printPath();
        break;
      }
      case 6:
      {
        C->reverseEntireNetwork();
        C->printPath();
        break;
      }
      case 7:
      {
        C->deleteEntireNetwork();
        break;
      }
    }
  }
  cout << "Quitting... cleaning up path: " << endl;
  C->printPath();
  C->deleteEntireNetwork();
  bool cleaned = C->isEmpty();
  if(cleaned)
    cout << "Path cleaned" << endl;
  else
    cout << "Error: Path NOT cleaned" << endl;

  cout << "Goodbye!" << endl;
}

/*
 * Purpose: displays a menu with options
 */
void displayMenu()
{
    //cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Delete Country " << endl;
    cout << " 6. Reverse Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
