/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 2
*/

#include "DecisionTreeNode.h"
#include <iostream>
#include <string>

using namespace std;

DecisionTreeNode::DecisionTreeNode()
{
    isLeaf = true;
    featureID = -1;
    classID = -2;
    left = NULL;
    right = NULL;
}

DecisionTreeNode::DecisionTreeNode(int feature)
{
    isLeaf = true;
    featureID = feature;
    classID = -2;
    left = NULL;
    right = NULL;
}

DecisionTreeNode& DecisionTreeNode::operator=(const DecisionTreeNode &node)
{
    isLeaf = node.isLeaf;
    featureID = node.featureID;
    classID = node.classID;
    left = node.left;
    right = node.right;
    return *this;
}

DecisionTreeNode::~DecisionTreeNode()
{
//    delete left;
//    delete right;
}

void DecisionTreeNode::deletePointers()
{
    delete left;
    delete right;
}

bool DecisionTreeNode::isLeafNode() const
{
    return isLeaf;
}

void DecisionTreeNode::setFeature(int feature)
{
    featureID = feature;
}

int DecisionTreeNode::getFeatureID()
{
    return featureID;
}

int DecisionTreeNode::getClassID()
{
    return classID;
}

void DecisionTreeNode::unsetLeafNode()
{
    isLeaf = false;
}

void DecisionTreeNode::makeLeafNode()
{
    isLeaf = true;
}

void DecisionTreeNode::setClassID(int classNum)
{
    classID = classNum;
}

DecisionTreeNode* DecisionTreeNode::getLeftNode()
{
    return left;
}

DecisionTreeNode* DecisionTreeNode::getRightNode()
{
    return right;
}

void DecisionTreeNode::addLeftNode(DecisionTreeNode*& nodeLeft)
{
    left = nodeLeft;
}

void DecisionTreeNode::addRightNode(DecisionTreeNode*& nodeRight)
{
    right = nodeRight;
}
