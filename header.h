#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

struct Node {
    int priority;
    string info;
    Node *left;
    Node *right;
};

typedef Node* adrNode;

adrNode createNode(int priority, string info);
adrNode insertNode(adrNode root, int priority, string info);
adrNode searchNode(adrNode root, int priority);
adrNode findMin(adrNode root);
adrNode deleteNode(adrNode root, int priority);
adrNode findSuccessor(adrNode root, int priority);
adrNode findPredecessor(adrNode root, int priority);

void inorder(adrNode root);
void preorder(adrNode root);
void postorder(adrNode root);

int countAtLevel(adrNode root, int level);
void searchRange(adrNode root, int low, int high);
void printTree(adrNode root, int space = 0, int gap = 10);

int height(adrNode root);
bool isBalanced(adrNode root);

void clearTree(adrNode &root);

#endif

