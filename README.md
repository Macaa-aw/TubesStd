# TubesStd
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
#include "Header.h"

/* Membuat node baru */
adrNode createNode(EmergencyCase ec) {
    adrNode newNode = new Node;
    newNode->data = ec;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* Insert data ke BST */
void insertCase(adrNode &root, EmergencyCase ec) {
    if (root == NULL) {
        root = createNode(ec);
    } else if (ec.priority < root->data.priority) {
        insertCase(root->left, ec);
    } else if (ec.priority > root->data.priority) {
        insertCase(root->right, ec);
    }
}

/* Mencari node berdasarkan priority */
adrNode searchNode(adrNode root, int priority) {
    if (root == NULL || root->data.priority == priority) {
        return root;
    } else if (priority < root->data.priority) {
        return searchNode(root->left, priority);
    } else {
        return searchNode(root->right, priority);
    }
}

/* Mencari node minimum */
adrNode findMin(adrNode root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

/* Mencari node maksimum */
adrNode findMax(adrNode root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

/* Menghapus node berdasarkan priority */
adrNode deleteCase(adrNode root, int priority) {
    if (root == NULL) return NULL;

    if (priority < root->data.priority) {
        root->left = deleteCase(root->left, priority);
    } else if (priority > root->data.priority) {
        root->right = deleteCase(root->right, priority);
    } else {
        // Node dengan 1 atau 0 anak
        if (root->left == NULL) {
            adrNode temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            adrNode temp = root->left;
            delete root;
            return temp;
        }

        // Node dengan 2 anak
        adrNode temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteCase(root->right, temp->data.priority);
    }
    return root;
}

/* Mencari successor */
adrNode findSuccessor(adrNode root, int priority) {
    adrNode successor = NULL;

    while (root != NULL) {
        if (priority < root->data.priority) {
            successor = root;
            root = root->left;
        }
        else if (priority > root->data.priority) {
            root = root->right;
        }
        else {
            if (root->right != NULL)
                successor = findMin(root->right);
            root = NULL;
        }
    }
    return successor;
}


/* Mencari predecessor */
adrNode findPredecessor(adrNode root, int priority) {
    adrNode predecessor = NULL;

    while (root != NULL) {
        if (priority > root->data.priority) {
            predecessor = root;
            root = root->right;
        }
        else if (priority < root->data.priority) {
            root = root->left;
        }
        else {
            if (root->left != NULL)
                predecessor = findMax(root->left);
            root = NULL;
        }
    }
    return predecessor;
}


/* Traversal inorder */
void inorder(adrNode root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "Priority: " << root->data.priority
             << " | Desc: " << root->data.description << endl;
        inorder(root->right);
    }
}

/* Menghitung jumlah node pada level tertentu */
int countAtLevel(adrNode root, int level) {
    if (root == NULL) return 0;
    if (level == 0) return 1;
    return countAtLevel(root->left, level - 1) +
           countAtLevel(root->right, level - 1);
}

/* Mencari data dalam range priority */
void searchRange(adrNode root, int low, int high) {
    if (root == NULL) return;

    if (root->data.priority > low)
        searchRange(root->left, low, high);

    if (root->data.priority >= low && root->data.priority <= high)
        cout << "Priority: " << root->data.priority
             << " | Desc: " << root->data.description << endl;

    if (root->data.priority < high)
        searchRange(root->right, low, high);
}

/* Print tree (visual) */
void printTree(adrNode root, int space) {
    if (root == NULL) return;

    space += 5;
    printTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << root->data.priority << endl;

    printTree(root->left, space);
}

#include <iostream>
#include "Header.h"

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
            cout << "Masukkan priority: ";
            cin >> ec.priority;
            cin.ignore();
            cout << "Masukkan deskripsi: ";
            getline(cin, ec.description);
            insertCase(root, ec);
        }
        else if (pilih == 2) {
            cout << "Masukkan priority yang dihapus: ";
            cin >> key;
            root = deleteCase(root, key);
        }
        else if (pilih == 3) {
            cout << "\nData inorder:\n";
            inorder(root);
        }
        else if (pilih == 4) {
            cout << "Masukkan priority: ";
            cin >> key;
            p = findSuccessor(root, key);
            if (p != NULL)
                cout << "Successor: " << p->data.priority << endl;
            else
                cout << "Tidak ada successor\n";
        }
        else if (pilih == 5) {
            cout << "Masukkan priority: ";
            cin >> key;
            p = findPredecessor(root, key);
            if (p != NULL)
                cout << "Predecessor: " << p->data.priority << endl;
            else
                cout << "Tidak ada predecessor\n";
        }
        else if (pilih == 6) {
            cout << "Masukkan level: ";
            cin >> level;
            cout << "Jumlah node pada level " << level
                 << " = " << countAtLevel(root, level) << endl;
        }
        else if (pilih == 7) {
            cout << "Masukkan range (low high): ";
            cin >> low >> high;
            searchRange(root, low, high);
        }
        else if (pilih == 8) {
            cout << "\nStruktur tree:\n";
            printTree(root, 0);
        }
        else if (pilih != 0) {
            cout << "Menu tidak valid!\n";
        }

    } while (pilih != 0);

    return 0;
}
