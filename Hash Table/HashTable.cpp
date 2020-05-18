/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 4
*/

#include "HashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable( const int tableSize, const CollisionStrategy option )
{
    hashTableSize = tableSize;
    strategy = option;
    curSize  = 0;
    table    = new int[tableSize];
    status   = new LocationStatus[tableSize];
    for(int i = 0; i < tableSize; i++)
        status[i] = EMPTY;
//    cout << strategy << endl;
}

HashTable::~HashTable()
{
    delete[] table;
    delete[] status;
}

bool HashTable::insert( const int item )
{
    if (curSize == hashTableSize)
    {
        cout << "HashTable full!" << endl;
        return false;
    }
    else
    {
        bool spaceFound = false;
        int index;
        index = item % hashTableSize;
        for (int i = 0; i < hashTableSize; i++)
        {
            if (strategy == LINEAR)
            {
                if (status[(index + i) % hashTableSize] != OCCUPIED)
                {
                    index = (index + i) % hashTableSize;
                    spaceFound = true;
                    break;
                }
            }
            else if (strategy == QUADRATIC)
            {
                if (status[(index + (i*i) ) % hashTableSize] != OCCUPIED)
                {
                    index = (index + (i*i) ) % hashTableSize;
                    spaceFound = true;
                    break;
                }
            }
            else
            {
                if (status[(index + (i * hash2Func(item)) ) % hashTableSize] != OCCUPIED)
                {
                    index = ( index + (i * hash2Func(item)) ) % hashTableSize;
                    spaceFound = true;
                    break;
                }
            }
        }
        if (spaceFound)
        {
            table[index]  = item;
            status[index] = OCCUPIED;
            curSize++;
//            cout << "Item added at index: "  << index << endl;
            return true;
        }
        else
        {
//            cout << "Failed to insert!" << endl;
            return false;
        }
    }
}

bool HashTable::remove( const int item )
{
    if (curSize == 0)
    {
        cout << "Hash table empty! Nothing here." << endl;
        return false;
    }
//    numProbes = 0;
    int index, index2;
    index = item % hashTableSize;
    index2 = index;
    for (int i = 1; i <= hashTableSize; i++)
    {
//        cout << "Checking at: " << index << endl;
//        numProbes++;
        if (status[index2] == OCCUPIED)
        {
            if (table[index2] == item)
            {
//                cout << "Item found!" << endl;
                status[index2] = DELETED;
                curSize--;
                return true;
            }
        }
        else if (status[index2] == EMPTY)
        {
//            cout << "Remove Unsuccessful! Item does not exist" << endl;
            return false;
        }
        if (strategy == LINEAR)
            index2 = index + i;
        else if (strategy == QUADRATIC)
            index2 = index + (i*i);
        else
            index2 = index + (i * hash2Func(item));
        index2 = index2 % hashTableSize;
    }
//    cout << "Item not found!" << endl;
    return false;
}

bool HashTable::search( const int item, int& numProbes )
{
    numProbes = 0;
    if (curSize == 0)
    {
        cout << "Hash table empty! Nothing here." << endl;
        return false;
    }
    int index, index2;
    index = item % hashTableSize;
    index2 = index;
    for (int i = 1; i <= hashTableSize; i++)
    {
//        cout << "Checking at: " << index << endl;
        numProbes++;
        if (status[index2] == OCCUPIED)
        {

            if (table[index2] == item)
            {
//                cout << "Item found!" << endl;
                return true;
            }
        }
        else if (status[index2] == EMPTY)
        {
//            cout << "Search Unsuccessful! Item does not exist" << endl;
            return false;
        }
        if (strategy == LINEAR)
            index2 = index + i;
        else if (strategy == QUADRATIC)
            index2 = index + (i*i);
        else
            index2 = index + (i * hash2Func(item));
        index2 = index2 % hashTableSize;
    }
//    cout << "Item not found!" << endl;
    return false;
}

void HashTable::display()
{
    for (int i = 0; i < hashTableSize; i++)
    {
        if (status[i] == OCCUPIED)
            cout << i << ": " << table[i] << endl;
        else
            cout << i << ": " << endl;
    }
}

void HashTable::analyze( int& numSuccProbes, int& numUnsuccProbes )
{
    int nProbes;
    // For successful search
    numSuccProbes = 0;
    for (int i = 0; i < hashTableSize; i++)
    {
        if (status[i] == OCCUPIED)
        {
            if (HashTable::search(table[i], nProbes))
                numSuccProbes += nProbes;
        }
    }

    // For unsuccessful search
    int index2;
    if (strategy == DOUBLE)
    {
        numUnsuccProbes = -1;
        return;
    }
    numUnsuccProbes = 0;
    for (int index = 0; index < hashTableSize; index++)
    {
        nProbes = 0;
        index2 = index;
        for (int i = 1; i <= hashTableSize; i++)
        {
            nProbes++;
            if (status[index2] == EMPTY)
            {
//                cout << "Search Unsuccessful! Item does not exist" << endl;
                break;
            }
            if (strategy == LINEAR)
                index2 = index + i;
            else if (strategy == QUADRATIC)
                index2 = index + (i*i);
            index2 = index2 % hashTableSize;
        }
        numUnsuccProbes += nProbes;
    }
}

double HashTable::getLoadFactor()
{
    return double(curSize)/double(hashTableSize);
}

int hash2Func(int num)
{
    int num2 = num;
    int mod, hash2 = 0;
    while(num2 != 0)
    {
        mod   = num2 % 10;
        hash2 = (hash2 * 10) + mod;
        num2 /= 10;
    }
    return hash2;
}
