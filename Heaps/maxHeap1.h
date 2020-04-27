/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 3
*/
#include <string>

using namespace std;

const int MAX_PATIENTS = 2000;
class maxHeap
{
public:
    struct Patient
    {
        int patientID;
        int priority;
        int arrivalTime;
        int serviceTime;
        int startTime;
        int waitTime;
        int doctorID;
    };
    maxHeap();
    bool heapIsEmpty() const;
    void heapInsert(Patient newItem);
	void heapDelete(Patient& rootItem);
	void heapDelete();
	int heapSize() const;
    void printHeap();
//    maxHeap1(const maxHeap1& aHeap); //copy constructor
//    maxHeap1& operator=(const maxHeap1 &aHeap); //assignment operator
private:
    Patient patients[MAX_PATIENTS];
    int numPatients;
    void heapRebuild(int root);
};
