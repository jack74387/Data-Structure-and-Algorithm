#ifndef TREENODE_H
#define TREENODE_H

#include<QPainter>
class TreeNode
{
public:
    TreeNode(char k);
    void insert(TreeNode*& node, char key);
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* node, char key);

    char key;
    TreeNode *left, *right;
};

#endif // TREENODE_H
