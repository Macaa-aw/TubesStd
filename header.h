#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
using namespace std;

typedef string infotype;
typedef struct Node *adrNode;


struct Node {
    int priority;
    infotype info;
    adrNode left;
    adrNode right;
};


adrNode createNode(int priority, infotype info);
adrNode findMin(adrNode root);
adrNode insertNode(adrNode root, int priority, infotype info);
adrNode deleteNode(adrNode root, int priority);
adrNode searchNode(adrNode root, int priority);
adrNode findSuccessor(adrNode root, int priority);
adrNode findPredecessor(adrNode root, int priority);
void inorder(adrNode root);
int countAtLevel(adrNode root, int level);
void searchRange(adrNode root, int low, int high);
void printTree(adrNode root, int space, int gap = 10);

#endif
