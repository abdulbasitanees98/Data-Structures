/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 2
*/

#include "DecisionTreeNode.h"
#include <string>

using namespace std;

class DecisionTree
{
private:
    DecisionTreeNode *root;
    int treeHeight;
    int featuresNum;
    double calculateEntropy(const int* classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
    void loadtxt(const string fileName, const int& numSamples, const int& numFeatures, bool** data, int* labels);
    void findRecursively(DecisionTreeNode *node, int level);
    void deleteRecursively(DecisionTreeNode *node);
    void split(DecisionTreeNode *&node, const bool** data, const int* labels, const int numSamples, const int numFeatures,  const bool* usedSamples, const bool* usedFeatures, int*& classes, int& numClasses);
    int predict1(const bool* data, DecisionTreeNode *node);
    void findClasses(const int* labels, const int numSamples, int*& classes, int& numClasses);
    void findClassCounts(const int* labels, int*& classes, int*& classCounts, int numClasses, int numSamples, const bool* usedSamples);
public:
    DecisionTree();
    ~DecisionTree();
    void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
    void train(const string fileName, const int numSamples, const int numFeatures);
    int predict(const bool* data);
    double test(const bool** data, const int* labels, const int numSamples);
    double test(const string fileName, const int numSamples);
    void print();
};
