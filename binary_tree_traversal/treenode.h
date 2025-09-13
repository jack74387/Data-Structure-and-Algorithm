#ifndef TREENODE_H
#define TREENODE_H

#include<QPainter>
class TreeNode
{
public:
    TreeNode();
    TreeNode* NEWnodeANDinputdata(int data, int dex);
    TreeNode* insert(TreeNode* node, int key, int dex);
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* node, int key);

    char key;
    int dex;
    TreeNode *left, *right;
};

#endif // TREENODE_H
