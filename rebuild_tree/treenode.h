#ifndef TREENODE_H
#define TREENODE_H

#include<QPainter>
class TreeNode
{
public:
    TreeNode();
    TreeNode* NEWnodeANDinputdata(int data, int index);
    TreeNode* insert(TreeNode* node, int key, int index);
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* node, int key);

    char key;
    int index;
    TreeNode *left, *right;
};

#endif // TREENODE_H
