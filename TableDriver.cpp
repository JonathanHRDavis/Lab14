#include "TableSortedList.h"
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   TableSortedList<CD>* slt = new TableSortedList<CD>(&CD::compare_items, &CD::compare_keys);

   //DO THIS
   //thoroughly test your table
   
      ListArrayIterator<CD>* iter = cds->iterator();
	  
	 String* titles[310]; 
	 CD* cds2[310];
	 int count = 0; 
	 
	 CD* duplicateTest; // test duplicate CD to be added later
	 
   while(iter->hasNext())
   {
      CD* cd = iter->next();
	  duplicateTest = cd;
	  
	  cds2[count]=cd;
	  titles[count]=cds2[count]->getKey();
	  count++;
	  
      slt->tableInsert(cd);
   }
   delete iter;
   
   slt->tableInsert(duplicateTest); // Program should not insert this CD because it is a duplicate
   
   cout << "Table size after inserting all CDs is " << slt->tableSize() << endl;	// If insert works correctly, size should be 310 (If duplicate was added, it would be 311)

   for(count = 0; count < 310; count++)
   {
	CD* cdRetrieve = slt->tableRetrieve(titles[count]);	// testing the retrieve function, it should be able to find all 310 CDs
	if (cdRetrieve == NULL)
	cout << "Couldn't find CD" << endl;
	else
	cout << "Found CD #" << count+1 << endl;
   }
	

   
   count = 1;
   
   ListDoublyLinkedIterator<CD>* iter2 = slt->iterator();	// Testing the SLDL iterator, every CD should be displayed
   
   while(iter2->hasNext())
   {
   CD* cd3 = iter2->next();

   cout << "\nThis is CD #" << count << ":" << endl << endl;
   count++;
   
   cd3->displayCD();
   }
   
   for(int i = 0; i < 310; i++)
   {
   slt->tableRemove(titles[i]);
   }
   
   	cout << "Table size after removing all CDs is " << slt->tableSize();	// Table size should be 0 after removing everything


   deleteCDs(cds);
   delete cds;
   delete slt;
   return 0;
}
