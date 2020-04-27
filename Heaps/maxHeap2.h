/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 3
*/
using namespace std;

//const int MAX_PATIENTS = 2000;

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
    ~maxHeap();
    bool heapIsEmpty() const;
    void heapInsert(Patient newItem);
	void heapDelete(Patient& rootItem);
	void heapDelete();
	int heapSize() const;
    void printHeap();
//    maxHeap(const maxHeap& aHeap); //copy constructor
//    maxHeap& operator=(const maxHeap &aHeap); //assignment operator
private:
    Patient* patients;
    int numPatients;
    int curSize;
    void heapRebuild(int root);
};

