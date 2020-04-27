/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 3
*/
#include "maxHeap2.h"
#include <iostream>

using namespace std;

maxHeap::maxHeap()
{
    curSize = 10;
    patients = new Patient[curSize];
    numPatients = 0;
}

maxHeap::~maxHeap()
{
    delete [] patients;
}

bool maxHeap::heapIsEmpty() const
{
	return (numPatients == 0);
}

int maxHeap::heapSize() const
{
    return numPatients;
}

void maxHeap::printHeap()
{
    cout << "Printing patient priority numbers in heap" << endl;
    if (heapIsEmpty())
        cout << "Heap empty" << endl;
    else
    {
        for (int i = 0; i < numPatients; i++)
            cout << patients[i].priority << "\t" << patients[i].arrivalTime << endl;
    }
}

void maxHeap::heapRebuild(int root) {
	int child = 2 * root + 1; 	// index of root's left child, if any
	if ( child < numPatients ) {
		// root is not a leaf so that it has a left child
		int rightChild = child + 1; 	// index of a right child, if any
		// If root has right child, find larger child
		if ( (rightChild < numPatients) && (patients[rightChild].priority > patients[child].priority) )
            child = rightChild; 	// index of larger child
        else if ((rightChild < numPatients) && (patients[rightChild].priority == patients[child].priority)) // Handle condition for same priority
        {
            if (patients[rightChild].arrivalTime < patients[child].arrivalTime)
                child = rightChild; 	// index of larger child
        }

		// If root’s item is smaller than larger child, swap values
		if ( patients[root].priority < patients[child].priority )
        {
			Patient temp = patients[root];
			patients[root] = patients[child];
			patients[child] = temp;
			heapRebuild(child); // transform the new subtree into a heap
        }
        else if ( patients[root].priority == patients[child].priority )
        {
             if (patients[root].arrivalTime > patients[child].arrivalTime) // Handle condition for same priority
             {
                Patient temp = patients[root];
                patients[root] = patients[child];
                patients[child] = temp;
                heapRebuild(child); // transform the new subtree into a heap
             }
        }
	}
}

void maxHeap::heapInsert(Patient newItem){

    if (numPatients == curSize)
    {
        curSize = 2 * curSize;
//        cout << "Expanding to " << curSize << endl;
        Patient* newPatients = new Patient[curSize];
        for (int i = 0; i < numPatients; i++)
            newPatients[i] = patients[i];
        delete [] patients;
        patients = newPatients;
    }
	patients[numPatients] = newItem;

	// Trickle new item up to its proper position
	int place = numPatients;
	int parent = (place - 1)/2;
	while ( (place > 0) && (patients[place].priority >= patients[parent].priority) ) {
        if (patients[place].priority == patients[parent].priority) // Handle condition for same priority
        {
            if (patients[place].arrivalTime >= patients[parent].arrivalTime)
                break;
        }
		Patient temp = patients[parent];
		patients[parent] = patients[place];
		patients[place] = temp;

		place = parent;
		parent = (place - 1)/2;
	}
 	++numPatients;
}

void maxHeap::heapDelete(){
	if (heapIsEmpty()){
		cout << "HeapException: Heap empty" << endl;
		return;
	}
	else {
//		cout << "Removing " << patients[0].priority << "\t" << patients[0].arrivalTime << endl;
		patients[0] = patients[--numPatients];
        heapRebuild(0);
	}
//	printHeap();
}

void maxHeap::heapDelete(Patient& rootItem){
	if (heapIsEmpty()){
		cout << "HeapException: Heap empty" << endl;
		return;
	}
	else {
		rootItem = patients[0];
//		cout << "Removing " << patients[0].priority << "\t" << patients[0].arrivalTime << endl;
		patients[0] = patients[--numPatients];
        heapRebuild(0);
	}
	if ( ((2*numPatients) < curSize) && curSize > 1 )
    {
        curSize = curSize/2;
//        cout << "Shrinking to " << curSize << endl;
        Patient* newPatients = new Patient[curSize];
        for (int i = 0; i < numPatients; i++)
            newPatients[i] = patients[i];
        delete [] patients;
        patients = newPatients;
    }
}
