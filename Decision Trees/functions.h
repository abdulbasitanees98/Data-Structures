/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 2
*/

#include <string>
using namespace std;

double calculateEntropy(const int* classCounts, const int numClasses);
double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
void findClasses(const int* labels, const int numSamples, int*& classes, int& numClasses);
void findClassCounts(const int* labels, int*& classes, int*& classCounts, int numClasses, int numSamples, const bool* usedSamples);
void getDataSize(const string trainDataPath, int& numSamples, int& numFeatures);
void loadtxt(const string trainDataPath, const int& numSamples, const int& numFeatures, bool** data, int* labels );
//template <typename type>
//void displayArray2d(type **arr, int row, int col);
//template <typename type>
//void displayArray(type *arr, int len)
