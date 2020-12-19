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
	cout<< "*----------------------------------------*"<<endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout<< "*----------------------------------------*"<<endl;
}










int main(int argc, char const *argv[])
{
		string input = "0";
		ProducerConsumer P;
		while(stoi(input) != 3)
		{
			menu();

			getline(cin, input);
			switch (stoi(input)) {
			case 1:
			{
				cout << "Enter the number of items to be produced:" << endl;
				string numItems = "";
				getline(cin, numItems);
				for (int i = 1 ; i <= stoi(numItems) ; i++)
				{
					cout << "Item" << i << ":" << endl;
					string item;
					getline (cin, item);
					P.enqueue(item);
				}
				break;
			}
			case 2:
			{
				cout << "Enter the number of items to be consumed:" << endl;
				string inp = "";
				getline(cin, inp);
				int numItems = stoi(inp);
				bool over = false;
				if(P.queueSize() < numItems)
				{
					numItems = P.queueSize();
					over = true;
				}
				for (int i = 1; i <= numItems; i++)
				{
					//string item = P.peek();
					cout << "Consumed: " << P.peek() << endl;
					P.dequeue();
				}
				if (over)
					cout<< "No more items to consume from queue" << endl;
				break;
			}
		}
	}
		cout << "Number of items in the queue:";
		cout<< P.queueSize() <<endl;
}
