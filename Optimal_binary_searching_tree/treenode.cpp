#include "treenode.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QPainter>
#include <QLabel>

TreeNode::TreeNode(char k) : key(k), left(nullptr), right(nullptr) {
}



/* A utility function to insert a new node with given key in BST */
void TreeNode::insert(TreeNode*& node, char key)
{
    if (node == nullptr) {
        node = new TreeNode(key);
    } else if (key < node->key) {
        insert(node->left, key);
    } else {
        insert(node->right, key);
    }
}
TreeNode* TreeNode::minValueNode(TreeNode* node)
{
    TreeNode* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
TreeNode* TreeNode::deleteNode(TreeNode* node, char key)
{
    // base case
    if (node == NULL)
        return node;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < node->key)
        node->left = deleteNode(node->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > node->key)
        node->right = deleteNode(node->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (node->left == NULL)
        {
            TreeNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL)
        {
            TreeNode *temp = node->left;
            delete node;
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        TreeNode* temp = minValueNode(node->right);

        // Copy the inorder successor's content to this node
        node->key = temp->key;

        // Delete the inorder successor
        node->right = deleteNode(node->right, temp->key);
    }
    return node;
}
