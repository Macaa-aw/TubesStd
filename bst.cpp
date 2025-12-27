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
    adrNode result = nullptr;

    if (root != nullptr) {
        if (root->priority == priority) {
            result = root;
        } else if (priority < root->priority) {
            result = searchNode(root->left, priority);
        } else {
            result = searchNode(root->right, priority);
        }
    }

    return result;
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

/* =====================
   FIND MIN
   ===================== */
adrNode findMin(adrNode root) {
    adrNode result = nullptr;

    if (root != nullptr) {
        while (root->left != nullptr) {
            root = root->left;
        }
        result = root;
    }

    return result;
}
/* =====================
   DELETE NODE
   ===================== */
adrNode deleteNode(adrNode root, int priority) {
    adrNode result = root;

    if (root != nullptr) {
        if (priority < root->priority) {
            root->left = deleteNode(root->left, priority);
        }
        else if (priority > root->priority) {
            root->right = deleteNode(root->right, priority);
        }
        else {
            // Kasus 1: Tidak punya child
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                result = nullptr;
            }
            // Kasus 2: Punya satu child
            else if (root->left == nullptr) {
                adrNode temp = root->right;
                delete root;
                result = temp;
            }
            else if (root->right == nullptr) {
                adrNode temp = root->left;
                delete root;
                result = temp;
            }
            // Kasus 3: Punya dua child
            else {
                adrNode temp = findMin(root->right);
                root->priority = temp->priority;
                root->info = temp->info;
                root->right = deleteNode(root->right, temp->priority);
            }
        }
    }

    return result;
}

void inorder(adrNode root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "Priority : " << root->priority
             << " | Info : " << root->info << endl;
        inorder(root->right);
    }
}


int countAtLevel(adrNode root, int level) {
    int count = 0;

    if (root != nullptr) {
        if (level == 0) {
            count = 1;
        } else {
            count = countAtLevel(root->left, level - 1) + countAtLevel(root->right, level - 1);
        }
    }

    return count;
}


void searchRange(adrNode root, int low, int high) {
    if (root == nullptr) {
        return;
    }

    if (low < root->priority) {
        searchRange(root->left, low, high);
    }

    if (low <= root->priority && root->priority <= high) {
        cout << "Priority : " << root->priority << " | Info : " << root->info << endl;
    }

    if (high > root->priority) {
        searchRange(root->right, low, high);
    }
}


void printTree(adrNode root, int space, int gap) {
    if (root == nullptr) {
        return;  // ← CUKUP RETURN SAJA, TANPA COUT
    }

    space += gap;

    // Print anak kanan dulu (atas)
    printTree(root->right, space, gap);

    // Print node saat ini
    cout << endl;
    for (int i = gap; i < space; i++) {
        cout << " ";
    }
    cout << "[" << root->priority << "] " << root->info << endl;

    // Print anak kiri (bawah)
    printTree(root->left, space, gap);
}
