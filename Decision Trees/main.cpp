/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 2
*/

#include "DecisionTree.h"
#include "functions.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    const string trainDataPath = "train_data.txt";
    const string testDataPath = "test_data.txt";
    // Determine data size
    int numSamples;
    int numFeatures;
    getDataSize(trainDataPath, numSamples, numFeatures);
    DecisionTree tree = DecisionTree();
    tree.train(trainDataPath, numSamples, numFeatures);
    cout << "Training done" << endl;
    tree.print();
    double accuracy;
    accuracy = tree.test(testDataPath, 473);
    cout << "Accuracy = " << accuracy << "%" << endl;
}
