/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 2
*/

#include "DecisionTree.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

DecisionTree::DecisionTree()
{
    root = new DecisionTreeNode();
    treeHeight = 1;
    featuresNum = 0;
}

DecisionTree::~DecisionTree()
{
//    cout << "Deconstructing" << endl;
    deleteRecursively(root);
//    cout << "Deconstructed" << endl;
}

void DecisionTree::deleteRecursively(DecisionTreeNode* node)
{
    if (!node->isLeafNode())
    {
        deleteRecursively(node->getLeftNode());
        deleteRecursively(node->getRightNode());
        node->makeLeafNode();
    }
//    cout << "Deleting Feature ID: " << node->getFeatureID() << endl;
    delete node;
}

void DecisionTree::findRecursively(DecisionTreeNode* node, int level)
{
    for (int i = 0; i < level-1; i++)
        cout << "\t";
    if (!node->isLeafNode())
    {
        cout << "Feature ID=" << node->getFeatureID() << endl;
        findRecursively(node->getLeftNode(), level + 1);
        findRecursively(node->getRightNode(), level + 1);
    }
    else
    {
        cout << "Class ID=" << node->getClassID() << endl;
    }
}

void DecisionTree::print()
{
    cout << "Printing Tree..." << endl;
    cout << "Height=" << treeHeight << endl;
    findRecursively(root, 1);
}

void DecisionTree::loadtxt(const string fileName, const int& numSamples, const int& numFeatures, bool** data, int* labels)
{
    featuresNum = numFeatures;
    ifstream dataFile(fileName.c_str());
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

double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses)
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

double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId)
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

void DecisionTree::findClasses(const int* labels, const int numSamples, int*& classes, int& numClasses)
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

void DecisionTree::findClassCounts(const int* labels, int*& classes, int*& classCounts, int numClasses, int numSamples, const bool* usedSamples)
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

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures)
{
    int* labels = new int[numSamples];
    bool** data = new bool*[numSamples];
    for(int i = 0; i < numSamples; i++)
        data[i] = new bool[numFeatures];
    loadtxt(fileName, numSamples, numFeatures, data, labels);
    train((const bool**) data, labels, numSamples, numFeatures);
    for(int i = 0; i < numSamples; i++)
        delete[] data[i];
    delete[] data;
    delete[] labels;
}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures)
{
    bool* usedSamples = new bool[numSamples];
    bool* usedFeatures = new bool[numSamples];
    for (int i =0; i < numSamples; i++)
    {
        usedSamples[i] = true;
        usedFeatures[i] = false;
    }
    int* classes = new int[100];
    int numClasses;
    findClasses(labels, numSamples, classes, numClasses);
//    for (int i =0; i < numClasses; i++)
//        cout << classes[i] << " ";
//    root.setClassID(5);
    split(root, (const bool**) data, labels, numSamples, numFeatures, usedSamples, usedFeatures, classes, numClasses);
//    cout << "Split completed" << endl;
//    cout << (root->getRightNode()->getRightNode()->getRightNode())->getClassID() << endl;
    delete [] usedSamples;
    delete [] usedFeatures;
    delete [] classes;
}

void DecisionTree::split(DecisionTreeNode *&node, const bool** data, const int* labels, const int numSamples, const int numFeatures,  const bool* usedSamples, const bool* usedFeatures, int*& classes, int& numClasses)
{
//    cout << "New Split" << endl;
    int* classCounts = new int[numClasses];
    findClassCounts(labels, classes, classCounts, numClasses, numSamples, usedSamples);
//    cout << endl;
//    for (int i =0; i < numClasses; i++)
//        cout << classCounts[i] << " ";
//    cout << endl;
//    cout << "Class counts: " << classCounts[0] << " " << classCounts[1] << " " << classCounts[2] << endl;
    // Check if node is pure.
    int zeroCount = 0;
    int nonZeroIndex = -1;
    for (int i = 0; i < numClasses; i++)
    {
        if (classCounts[i] == 0)
            zeroCount++;
        else
            nonZeroIndex = i;
    }
    bool pure = (zeroCount == numClasses - 1);
    if (pure)
    {
        node->setClassID(classes[nonZeroIndex]);
        delete [] classCounts;
//        cout << "Node is pure" << endl;
        return;
    }
    // Check if all features have been used
    bool leaf = true;
    for (int i = 0; i < numFeatures; i++)
    {
        if (usedFeatures[i] == false)
            leaf = false;
//        cout << usedFeatures[i] << " ";
    }
    if (leaf) // Then set it as leaf node and predict
    {
//        cout << "The unpassable" << endl;
        int mostFreqClassIndex = 0;
        int maxCounts = 0;
        for (int i = 0; i < numClasses; i++)
        {
            if (classCounts[i] > maxCounts)
            {
                maxCounts = classCounts[i];
                mostFreqClassIndex = i;
            }
        }
        node->setClassID(classes[mostFreqClassIndex]);
        delete [] classCounts;
//        cout << "Majority voting" << endl;
        return;
    }
    else // if not null??
    {
        treeHeight++;
        node->unsetLeafNode();
        delete [] classCounts;
        // Find best feature for split
        double IG;
        double maxIG = -1;
        int bestFeature = -1;
        for (int i = 0; i < numFeatures; i++)
        {
            if (usedFeatures[i] == false)
            {
                IG = calculateInformationGain((const bool**) data, labels, numSamples, numFeatures, usedSamples, i);
                if (IG > maxIG)
                {
                    maxIG = IG;
                    bestFeature = i;
                }
            }
        }
//        cout << "Feature for Split: " << bestFeature << endl;
        node->setFeature(bestFeature);
        bool* usedFeaturesNew = new bool[numSamples];
        for (int i = 0; i < numFeatures; i++)
            usedFeaturesNew[i] = usedFeatures[i];
        usedFeaturesNew[bestFeature] = true;
        // Find frequency of classes in splits and number of samples in each split
        bool* usedSamplesL = new bool[numSamples];
        bool* usedSamplesR = new bool[numSamples];
        for (int i = 0; i < numSamples; i++)
        {
            usedSamplesL[i] = false;
            usedSamplesR[i] = false;
            if (usedSamples[i])
            {
                if (data[i][bestFeature])
                    usedSamplesR[i] = true;
                else
                    usedSamplesL[i] = true;
            }
        }
        // Following will be deleted by the class deconstructor
        DecisionTreeNode *leftNode = new DecisionTreeNode();
        DecisionTreeNode *rightNode = new DecisionTreeNode();
//        cout << "Before: " << leftNode.getClassID() << endl;
        split(leftNode, (const bool**) data, labels, numSamples, numFeatures, usedSamplesL, usedFeaturesNew, classes, numClasses);
//        cout << "After: " << leftNode.getClassID() << endl;
//        cout << "Here" << endl;
        node->addLeftNode(leftNode);
        split(rightNode, (const bool**) data, labels, numSamples, numFeatures, usedSamplesR, usedFeaturesNew, classes, numClasses);
        node->addRightNode(rightNode);
//        cout << (root.getRightNode().getRightNode()).getFeatureID() << endl;
//        node.addNodes(leftNode, rightNode);
        delete [] usedSamplesL;
        delete [] usedSamplesR;
        delete [] usedFeaturesNew;
        return;
    }
    return;
}

int DecisionTree::predict1(const bool* data, DecisionTreeNode *node)
{
    if (node->isLeafNode())
        return node->getClassID();
    else
    {
        int featureID = node->getFeatureID();
        if (data[featureID])
            return predict1(data, node->getRightNode());
        else
            return predict1(data, node->getLeftNode());
    }
}

int DecisionTree::predict(const bool* data)
{
    return predict1(data, root);
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples)
{
    bool* dataRow = new bool[featuresNum];
    int label;
    int labelPredicted;
    double trueLabels = 0;
    for(int i = 0; i < numSamples; i++)
    {
        for(int j = 0; j < featuresNum; j++)
            dataRow[j] = data[i][j];
        label = labels[i];
        labelPredicted = predict(dataRow);
        if (labelPredicted == label)
            trueLabels++;
    }
    delete [] dataRow;
    double totalSamples = numSamples;
    double accuracy;
    accuracy = 100.0 * (trueLabels / totalSamples);
    return accuracy;
}

double DecisionTree::test(const string fileName, const int numSamples)
{
    int* labels = new int[numSamples];
    bool** data = new bool*[numSamples];
    for(int i = 0; i < numSamples; i++)
        data[i] = new bool[featuresNum];
    loadtxt(fileName, numSamples, featuresNum, data, labels);
    double accuracy;
    accuracy = test((const bool**) data, labels, numSamples);
    for(int i = 0; i < numSamples; i++)
        delete[] data[i];
    delete[] data;
    delete[] labels;
    return accuracy;
}
