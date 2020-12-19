#include "HashTable.hpp"
#include <iostream>
#include <fstream>


int main(int argc, char* argv[])
{

  //initialize hashtable
  HashTable* stopWordsTable = new HashTable(50); //argv[3]
  getStopWords(argv[3], *stopWordsTable); //read ignore file

  HashTable* uniqueWords = new HashTable(std::stoi(argv[4])); //argv[4] = size

  std::ifstream readFile;
  readFile.open(argv[2]); //file to be read
  std::string word;
  while(readFile>>word)
  {
      if (!isStopWord(word, *stopWordsTable))
      {
        if(!uniqueWords->isInTable(word))
          uniqueWords->addWord(word);
        else
          uniqueWords->incrementCount(word);
      }
  }
  uniqueWords->printTopN(std::stoi(argv[1]));
  std::cout<<"#"<<std::endl;
  std::cout<<"Number of collisions: "<<uniqueWords->getNumCollisions()<<std::endl;
  std::cout<<"#"<<std::endl;
  std::cout<<"Unique non-stop words: "<<uniqueWords->getNumItems()<<std::endl;
  std::cout<<"#"<<std::endl;
  std::cout<<"Total non-stop words: "<<uniqueWords->getTotalNumWords()<<std::endl;
}
