# TubesStd
#ifndef EMERGENCY_PRIORITY_H
#define EMERGENCY_PRIORITY_H
#include <iostream>
#include <string>
using namespace std;
typedef struct Node *adrNode;

struct EmergencyCase {
    int priority;
    string description;
};

struct Node {
    EmergencyCase data;
    adrNode left;
    adrNode right;
};

adrNode createNode(EmergencyCase ec);
void insertCase(adrNode &root, EmergencyCase ec);
adrNode deleteCase(adrNode root, int priority);
adrNode searchNode(adrNode root, int priority);
adrNode findMin(adrNode root);
adrNode findMax(adrNode root);
adrNode findSuccessor(adrNode root, int priority);
adrNode findPredecessor(adrNode root, int priority);
void inorder(adrNode root);
int countAtLevel(adrNode root, int level);
void searchRange(adrNode root, int low, int high);
void printTree(adrNode root, int space);

#endif
#include "emergency_priority.h"

adrNode createNode(EmergencyCase ec) {
    adrNode p = new Node;
    p->data = ec;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void insertCase(adrNode &root, EmergencyCase ec) {
    if (root == NULL) {
        root = createNode(ec);
    } else if (ec.priority < root->data.priority) {
        insertCase(root->left, ec);
    } else if (ec.priority > root->data.priority) {
        insertCase(root->right, ec);
    }
}

adrNode findMin(adrNode root) {
    if (root->left == NULL)
        return root;
    return findMin(root->left);
}

adrNode findMax(adrNode root) {
    if (root->right == NULL)
        return root;
    return findMax(root->right);
}

adrNode deleteCase(adrNode root, int priority) {
    if (root == NULL) return NULL;

    if (priority < root->data.priority) {
        root->left = deleteCase(root->left, priority);
    } else if (priority > root->data.priority) {
        root->right = deleteCase(root->right, priority);
    } else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        } else if (root->left == NULL) {
            adrNode temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == NULL) {
            adrNode temp = root;
            root = root->left;
            delete temp;
        } else {
            adrNode temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteCase(root->right, temp->data.priority);
        }
    }
    return root;
}

adrNode searchNode(adrNode root, int priority) {
    if (root == NULL || root->data.priority == priority)
        return root;
    if (priority < root->data.priority)
        return searchNode(root->left, priority);
    return searchNode(root->right, priority);
}

adrNode findSuccessor(adrNode root, int priority) {
    adrNode curr = searchNode(root, priority);
    if (curr == NULL) return NULL;
    if (curr->right != NULL)
        return findMin(curr->right);

    adrNode succ = NULL;
    while (root != NULL) {
        if (priority < root->data.priority) {
            succ = root;
            root = root->left;
        } else if (priority > root->data.priority) {
            root = root->right;
        } else break;
    }
    return succ;
}

adrNode findPredecessor(adrNode root, int priority) {
    adrNode curr = searchNode(root, priority);
    if (curr == NULL) return NULL;
    if (curr->left != NULL)
        return findMax(curr->left);

    adrNode pred = NULL;
    while (root != NULL) {
        if (priority > root->data.priority) {
            pred = root;
            root = root->right;
        } else if (priority < root->data.priority) {
            root = root->left;
        } else break;
    }
    return pred;
}

void inorder(adrNode root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data.priority << " - "
             << root->data.description << endl;
        inorder(root->right);
    }
}

int countAtLevel(adrNode root, int level) {
    if (root == NULL) return 0;
    if (level == 0) return 1;
    return countAtLevel(root->left, level - 1)
         + countAtLevel(root->right, level - 1);
}

void searchRange(adrNode root, int low, int high) {
    if (root != NULL) {
        if (root->data.priority > low)
            searchRange(root->left, low, high);
        if (root->data.priority >= low &&
            root->data.priority <= high)
            cout << root->data.priority << " - "
                 << root->data.description << endl;
        if (root->data.priority < high)
            searchRange(root->right, low, high);
    }
}

void printTree(adrNode root, int space) {
    if (root != NULL) {
        space += 5;
        printTree(root->right, space);
        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << root->data.priority;
        printTree(root->left, space);
    }
}
#include <iostream>
#include "emergency_priority.h"

int main() {
    adrNode root = NULL;
    EmergencyCase ec;
    int pilih, key, level, low, high;
    adrNode p;

    do {
        cout << "\n=== SISTEM PRIORITAS DARURAT ===\n";
        cout << "1. Tambah kasus\n";
        cout << "2. Hapus kasus\n";
        cout << "3. Tampilkan inorder\n";
        cout << "4. Cari successor\n";
        cout << "5. Cari predecessor\n";
        cout << "6. Hitung node level\n";
        cout << "7. Cari range prioritas\n";
        cout << "8. Tampilkan struktur\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            cin >> ec.priority;
            cin.ignore();
            getline(cin, ec.description);
            insertCase(root, ec);
        }
        else if (pilih == 2) {
            cin >> key;
            root = deleteCase(root, key);
        }
        else if (pilih == 3) {
            inorder(root);
        }
        else if (pilih == 4) {
            cin >> key;
            p = findSuccessor(root, key);
            if (p != NULL)
                cout << p->data.priority;
            else
                cout << "Tidak ada";
        }
        else if (pilih == 5) {
            cin >> key;
            p = findPredecessor(root, key);
            if (p != NULL)
                cout << p->data.priority;
            else
                cout << "Tidak ada";
        }
        else if (pilih == 6) {
            cin >> level;
            cout << countAtLevel(root, level);
        }
        else if (pilih == 7) {
            cin >> low >> high;
            searchRange(root, low, high);
        }
        else if (pilih == 8) {
            printTree(root, 0);
        }

    } while (pilih != 0);

    return 0;
}

