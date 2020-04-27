/**
* Author : Abdul Basit Anees
* ID: 21600659
* Section : 3
* Assignment : 2
*/

using namespace std;

class DecisionTreeNode
{
private:
    bool isLeaf;
    int featureID;
    int classID;
    DecisionTreeNode *left, *right;
public:
    DecisionTreeNode();
    DecisionTreeNode(int feature);
    DecisionTreeNode& operator=(const DecisionTreeNode &node);
    ~DecisionTreeNode();
    void deletePointers();
    bool isLeafNode() const;
    void setFeature(int feature);
    int getFeatureID();
    int getClassID();
    void unsetLeafNode();
    void makeLeafNode();
    void setClassID(int classNum);
    void addNodes();
    void addLeftNode(DecisionTreeNode*& nodeLeft);
    void addRightNode(DecisionTreeNode*& nodeRight);

    DecisionTreeNode* getLeftNode();
    DecisionTreeNode* getRightNode();
//    DecisionTreeNode(int* usedSamples);
};
