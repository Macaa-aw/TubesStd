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

/* ==== PROTOTYPE ==== */
adrNode createNode(int priority, string info);
adrNode insertNode(adrNode root, int priority, string info);
adrNode searchNode(adrNode root, int priority);
adrNode findMin(adrNode root);
adrNode deleteNode(adrNode root, int priority);
adrNode findSuccessor(adrNode root, int priority);
adrNode findPredecessor(adrNode root, int priority);
void inorder(adrNode root);
int countAtLevel(adrNode root, int level);
void searchRange(adrNode root, int low, int high);
void printTree(adrNode root, int space, int gap);

#endif
