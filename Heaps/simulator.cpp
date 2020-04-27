/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 3
*/

#include "maxHeap1.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

int simulator(char*& fileName, int avgWaitingTime)
{
    maxHeap heap = maxHeap();
    ifstream dataFile(fileName);
    string line;
//    maxHeap2 heap = maxHeap2();
    maxHeap::Patient patient1;
    int totalPatients;
    if (dataFile.is_open()) // Find number of total patients: Read first line
    {
        getline(dataFile, line);
        istringstream iss(line);
        iss >> totalPatients;
    }
    dataFile.close();
//    cout << totalPatients << " patients in the file!" << endl;
    int patientsArrived, nTime, numAvDoctors, nAttended;
    double totalWait;
    double avgWait = 100000000;
    numAvDoctors = 0;
    maxHeap::Patient attendedPatients[totalPatients];
    while (avgWait > double(avgWaitingTime))
    {
        totalWait = 0;
        nAttended = 0;
        numAvDoctors++;
        int avDoctors[numAvDoctors]; // index of array corresponds to doctor id
        for (int i = 0; i < numAvDoctors; i++)
            avDoctors[i] = -1; // -1 means free, number corresponds to busy doctor with, number = index of patient
        nTime = 0;
        patientsArrived = 0;
    //    int timestep;
    //    cout<< "Step time?" << endl;
    //    cin >> timestep;
        while(nAttended < totalPatients){ // start simulation by moving time forward
            ++nTime;
    //        cout << "Time: " << nTime << endl;
            ifstream dataFile(fileName);
            if (dataFile.is_open())
            {
                for (int i = 0; i < patientsArrived + 1; i++) // skip numPatients + 1 lines
                    getline(dataFile, line);
                for (int i = 0; i < totalPatients-patientsArrived; i++)
                {
                    getline(dataFile, line);
                    istringstream iss(line);
                    iss >> patient1.patientID;
                    iss >> patient1.priority;
                    iss >> patient1.arrivalTime;
                    iss >> patient1.serviceTime;
                    if (patient1.arrivalTime == nTime)
                    {
                        heap.heapInsert(patient1);
                        ++patientsArrived;
                    }
                    else
                        break;
                }
                dataFile.close();
            }
            else
                cout << "Unable to open file";
    //        heap.printHeap();

            for(int i = 0; (i < numAvDoctors) && (!heap.heapIsEmpty()); i++) // check for available doctors and assign patients
            {
                if (avDoctors[i] == -1)
                {
                    if (!heap.heapIsEmpty())
                    {
                        heap.heapDelete(attendedPatients[nAttended]);
                        avDoctors[i] = nAttended;
                        attendedPatients[nAttended].waitTime = nTime - attendedPatients[nAttended].arrivalTime;
                        totalWait = totalWait + attendedPatients[nAttended].waitTime;
                        attendedPatients[nAttended].startTime = nTime;
                        attendedPatients[nAttended].doctorID = i;
//                        cout << "Doctor " << i << " takes patient " << attendedPatients[nAttended].patientID << " at minute " << nTime << " (wait: " << attendedPatients[nAttended].waitTime << "mins)" << endl;
                        ++nAttended;
                    }
                }
                else
                {
                    int id = avDoctors[i];
                    if ((nTime - attendedPatients[id].startTime) == attendedPatients[id].serviceTime) // service time complete
                    {
                        avDoctors[i] = -1; // doctor free
    //                    ++nFinished;
                        if (!heap.heapIsEmpty())
                        {
                            heap.heapDelete(attendedPatients[nAttended]);
                            avDoctors[i] = nAttended;
                            attendedPatients[nAttended].waitTime = nTime - attendedPatients[nAttended].arrivalTime;
                            totalWait = totalWait + attendedPatients[nAttended].waitTime;
                            attendedPatients[nAttended].startTime = nTime;
                            attendedPatients[nAttended].doctorID = i;
//                            cout << "Doctor " << i << " takes patient " << attendedPatients[nAttended].patientID << " at minute " << nTime << " (wait: " << attendedPatients[nAttended].waitTime << "mins)" << endl;
                            ++nAttended;
                        }
                    }
                }
            }
        }
        avgWait = (totalWait / ((double)totalPatients));
    }
    cout << "Min Doctors needed: " << numAvDoctors << endl;
    cout << endl;
    cout << "Simulation with " << numAvDoctors << " doctors" << endl;
    cout << endl;
    for (int i = 0; i < totalPatients; i++)
    {
        cout << "Doctor " << attendedPatients[i].doctorID << " takes patient " << attendedPatients[i].patientID << " at minute " << attendedPatients[i].startTime << " (wait: " << attendedPatients[i].waitTime << "mins)" << endl;
    }
    cout << endl;
    cout << "Average waiting time: " << avgWait << " minutes" << endl;
    return numAvDoctors;
}

int main(int argc, char* argv[])
{
    char* fileName = argv[1];
    int wait = atoi(argv[2]);
    simulator(fileName, wait);
}
