/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 4
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>
#include "HashTable.h"

using namespace std;

void driver(char*& fileName, int tableSize, CollisionStrategy strategy)
{
    HashTable table = HashTable(tableSize, strategy);
    // Read file and perform operations
    ifstream dataFile(fileName);
    string line;
    int totalLines, item, nProbes;
    string operation;
    if (dataFile.is_open())
    {
        while(dataFile.peek() != EOF)
        {
            getline(dataFile, line);
            istringstream iss(line);
            iss >> operation;
            iss >> item;
            if (operation == "I")
                if (table.insert(item))
                    cout << item << " inserted" << endl;
                else
                    cout << item << " not inserted" << endl;
            else if (operation == "R")
                if (table.remove(item))
                    cout << item << " removed" << endl;
                else
                    cout << item << " not removed" << endl;
            else if (operation == "S")
            {
                if (table.search(item, nProbes))
                    cout << item << " found after " << nProbes << " probes" << endl;
                else
                    cout << item << " not found after " << nProbes << " probes" << endl;
            }
        }
    }
    else
        cout << "File could not be opened!" << endl;

    table.display();
    // Analyze
    double loadFactor = table.getLoadFactor();
    cout << "Load factor: " << loadFactor << endl;
    int nSucc, nUnSucc;
    table.analyze(nSucc, nUnSucc);
    cout << "Average empirical Successful probes: " << double(nSucc)/double(tableSize) << endl;
    if (strategy != DOUBLE)
        cout << "Average empirical UnSuccessful probes: " << double(nUnSucc)/double(tableSize) << endl;
    else
        cout << "Average empirical UnSuccessful probes: " << nUnSucc << endl;
    double probes;
    double term = 1-loadFactor;
    if (strategy == LINEAR)
    {
        probes = 0.5*(1+(1/term));
        cout << "Average theoretical Successful probes: " << probes << endl;
        probes = 0.5*(1+(1/(term*term)));
        cout << "Average theoretical UnSuccessful probes: " << probes << endl;
    }
    else
    {
        probes = -log(term)/loadFactor;
        cout << "Average theoretical Successful probes: " << probes << endl;
        probes = 1/term;
        cout << "Average theoretical UnSuccessful probes: " << probes << endl;
    }
}
int main()
{
    char* fileName = "data.txt";
    int tableSize = 29;
    CollisionStrategy strategy = DOUBLE;
    driver(fileName, tableSize, strategy);
}
