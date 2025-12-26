# TubesStd
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
void printTree(adrNode root, int space = 0, int gap = 10);

#endif

#include "Header.h"

/* =====================
   CREATE NODE
   ===================== */
adrNode createNode(int priority, infotype info) {
    adrNode p = new Node;
    p->priority = priority;
    p->info = info;
    p->left = nullptr;
    p->right = nullptr;
    return p;
}

/* =====================
   INSERT NODE
   ===================== */
adrNode insertNode(adrNode root, int priority, infotype info) {
    if (root == nullptr) {
        return createNode(priority, info);
    }

    if (priority < root->priority) {
        root->left = insertNode(root->left, priority, info);
    }
    else if (priority > root->priority) {
        root->right = insertNode(root->right, priority, info);
    }

    return root;
}

/* =====================
   SEARCH NODE
   ===================== */
adrNode searchNode(adrNode root, int priority) {
    if (root == nullptr || root->priority == priority) {
        return root;
    }

    if (priority < root->priority) {
        return searchNode(root->left, priority);
    }

    return searchNode(root->right, priority);
}

/* =====================
   FIND MIN
   ===================== */
adrNode findMin(adrNode root) {
    if (root == nullptr) {
        return nullptr;
    }

    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

/* =====================
   DELETE NODE
   ===================== */
adrNode deleteNode(adrNode root, int priority) {
    if (root == nullptr) {
        return nullptr;
    }

    if (priority < root->priority) {
        root->left = deleteNode(root->left, priority);
    }
    else if (priority > root->priority) {
        root->right = deleteNode(root->right, priority);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        if (root->left == nullptr) {
            adrNode temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == nullptr) {
            adrNode temp = root->left;
            delete root;
            return temp;
        }

        adrNode temp = findMin(root->right);
        root->priority = temp->priority;
        root->info = temp->info;
        root->right = deleteNode(root->right, temp->priority);
    }

    return root;
}


adrNode findSuccessor(adrNode root, int priority) {
    adrNode succ = nullptr;

    while (root != nullptr) {
        if (priority < root->priority) {
            succ = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}


adrNode findPredecessor(adrNode root, int priority) {
    adrNode pred = nullptr;

    while (root != nullptr) {
        if (priority > root->priority) {
            pred = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return pred;
}


void inorder(adrNode root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "Priority : " << root->priority << " | Info : " << root->info << endl;
        inorder(root->right);
    }
}


int countAtLevel(adrNode root, int level) {
    if (root == nullptr) {
        return 0;
    }
    if (level == 0) {
        return 1;
    }
    return countAtLevel(root->left, level - 1) + countAtLevel(root->right, level - 1);
}


void searchRange(adrNode root, int low, int high) {
    if (root == nullptr) {
        return;
    }

    if (low < root->priority) {
        searchRange(root->left, low, high);
    }

    if (low <= root->priority && root->priority <= high) {
        cout << "Priority : " << root->priority
             << " | Info : " << root->info << endl;
    }

    if (high > root->priority) {
        searchRange(root->right, low, high);
    }
}


void printTree(adrNode root, int space, int gap) {
    if (root == nullptr) {
        return;
    }

    space += gap;
    printTree(root->right, space, gap);

    cout << endl;
    for (int i = gap; i < space; i++) {
        cout << " ";
    }
    cout << root->priority << endl;

    printTree(root->left, space, gap);
}

#include <iostream>
#include "Header.h"

#include "Header.h"

int main() {
    adrNode root = nullptr;
    int pilih = -1;

    while (pilih != 0) {
        cout << "\n=== SISTEM MANAJEMEN PRIORITAS DARURAT ===\n";
        cout << "1. Insert Kasus\n";
        cout << "2. Delete Kasus\n";
        cout << "3. Search Kasus\n";
        cout << "4. Tampilkan Inorder\n";
        cout << "5. Cari Successor\n";
        cout << "6. Cari Predecessor\n";
        cout << "7. Hitung Node Pada Level\n";
        cout << "8. Cari Berdasarkan Range Prioritas\n";
        cout << "9. Print Tree\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {

        case 1: {
            int pr;
            infotype info;
            cout << "Priority : ";
            cin >> pr;
            cin.ignore();
            cout << "Info     : ";
            getline(cin, info);
            root = insertNode(root, pr, info);
            break;
        }

        case 2: {
            int pr;
            cout << "Priority yang dihapus: ";
            cin >> pr;
            root = deleteNode(root, pr);
            break;
        }

        case 3: {
            int pr;
            cout << "Priority dicari: ";
            cin >> pr;
            adrNode hasil = searchNode(root, pr);
            if (hasil != nullptr)
                cout << "Ditemukan: " << hasil->info << endl;
            else
                cout << "Data tidak ditemukan\n";
            break;
        }

        case 4:
            inorder(root);
            break;

        case 5: {
            int pr;
            cout << "Priority: ";
            cin >> pr;
            adrNode s = findSuccessor(root, pr);
            if (s != nullptr)
                cout << "Successor: " << s->priority << endl;
            else
                cout << "Tidak ada successor\n";
            break;
        }

        case 6: {
            int pr;
            cout << "Priority: ";
            cin >> pr;
            adrNode p = findPredecessor(root, pr);
            if (p != nullptr)
                cout << "Predecessor: " << p->priority << endl;
            else
                cout << "Tidak ada predecessor\n";
            break;
        }

        case 7: {
            int lvl;
            cout << "Level: ";
            cin >> lvl;
            cout << "Jumlah node di level " << lvl << " = " << countAtLevel(root, lvl) << endl;
            break;
}



