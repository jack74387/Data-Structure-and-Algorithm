#ifndef TREENODE_H
#define TREENODE_H

#include<QPainter>
class TreeNode
{
public:
    TreeNode();
    TreeNode* NEWnodeANDinputdata(int data);
    TreeNode* insert(TreeNode* node, int key);
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* node, int key);

    char key;
    TreeNode *left, *right;
};

#endif // TREENODE_H
