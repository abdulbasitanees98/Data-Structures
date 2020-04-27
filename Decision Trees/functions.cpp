/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 2
*/

#include "functions.h"
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>

double calculateEntropy(const int* classCounts, const int numClasses)
{
    double totalCount;
    totalCount = 0;
    for (int i = 0; i < numClasses; i++)
        totalCount = totalCount + classCounts[i];
    double H;
    H = 0;
    for (int i = 0; i < numClasses; i++)
    {
        if (classCounts[i] > 0)
            H = H - ((classCounts[i] / totalCount) * log2(classCounts[i] / totalCount));
    }
    return H;
}

double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId)
{
    int* classes = new int[100];
    int numClasses;
    findClasses(labels, numSamples, classes, numClasses);
    // Calculate class counts for parent node and calculate entropy
    int* classCounts = new int[numClasses];
    findClassCounts(labels, classes, classCounts, numClasses, numSamples, usedSamples);
    double parentEntropy;
    parentEntropy = calculateEntropy(classCounts, numClasses);
    delete[] classCounts;
    // Calculate class counts for child nodes after split and calculate entropies
    int* classCountsL = new int[numClasses];
    int* classCountsR = new int[numClasses];
    double countL = 0;
    double countR = 0;
    for (int i = 0; i < numClasses; i++)
    {
        classCountsL[i] = 0;
        classCountsR[i] = 0;
    }
    for (int i = 0; i < numSamples; i++)
    {
        if (usedSamples[i])
        {
            if (data[i][featureId])
            {
                for (int j = 0; j < numClasses; j++)
                {
                    if (labels[i] == classes[j])
                    {
                        classCountsR[j]++;
                    }
                }
                countR++;
            }
            else
            {
                for (int j = 0; j < numClasses; j++)
                {
                    if (labels[i] == classes[j])
                    {
                        classCountsL[j]++;
                    }
                }
                countL++;
            }
        }
    }
    double childLEntropy, childREntropy;
    childLEntropy = calculateEntropy(classCountsL, numClasses);
    childREntropy = calculateEntropy(classCountsR, numClasses);
    delete[] classCountsL;
    delete[] classCountsR;
    delete[] classes;
    double childEntropyWeighted, probR;
    probR = countR / (countR + countL);
    childEntropyWeighted = (probR * childREntropy) + ((1- probR) * childLEntropy);
    double InformationGain;
    InformationGain = parentEntropy - childEntropyWeighted;
    return InformationGain;
}

void findClasses(const int* labels, const int numSamples, int*& classes, int& numClasses)
{
    bool found = false;
    numClasses = 0;
    classes[0] = labels[0];
    numClasses++;
    for (int i =0; i < numSamples; i++)
    {
        for (int j =0; j < numClasses; j++)
        {
            if (labels[i] == classes[j])
                found = true;
        }
        if (!found)
        {
            classes[numClasses] = labels[i];
            numClasses++;
        }
        found = false;
    }
}

void findClassCounts(const int* labels, int*& classes, int*& classCounts, int numClasses, int numSamples, const bool* usedSamples)
{
    for (int i = 0; i < numClasses; i++)
        classCounts[i] = 0;
    for (int i = 0; i < numSamples; i++)
    {
        if (usedSamples[i])
        {
            for (int j = 0; j < numClasses; j++)
            {
                if (labels[i] == classes[j])
                {
                    classCounts[j]++;
                }
            }
        }
    }
}

//template <typename type>
//void displayArray(type *arr, int len)
//{
//    for (int i = 0; i < len; i++)
//        cout << arr[i] << " ";
//    cout << endl;
//}
//
//template <typename type>
//void displayArray2d(type **arr, int row, int col)
//{
//    for (int i = 0; i < row; i++)
//    {
//        for (int j = 0; j < col; j++)
//            cout << arr[i][j] << " ";
//        cout << endl;
//    }
//}

void getDataSize(const string trainDataPath, int& numSamples, int& numFeatures)
{
    ifstream dataFile(trainDataPath.c_str());
    string line;
    numSamples = 0;
    numFeatures = 0;
    if (dataFile.is_open())
    {
        while (std::getline(dataFile, line))  // this does the checking!
        {
            numSamples++;
            std::istringstream iss(line);
            int c;
            while (iss >> c)
            {
                if (numSamples == 1)
                    numFeatures++;
            }
            if (numSamples == 1)
                numFeatures--; //One of them is label
        }
        dataFile.close();
    }
    else
        cout << "Unable to open file";
}

void loadtxt(const string trainDataPath, const int& numSamples, const int& numFeatures, bool** data, int* labels )
{
    ifstream dataFile(trainDataPath.c_str());
    string line;
    if (dataFile.is_open())
    {
        for (int i = 0; i < numSamples; i++)
        {
            std::getline(dataFile, line);
            std::istringstream iss(line);
            for (int j = 0; j < numFeatures; j++)
                iss >> data[i][j];
            iss >> labels[i];
        }
        dataFile.close();
    }
    else
        cout << "Unable to open file";
}

