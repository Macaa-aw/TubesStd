#include "header.h"

/* ===================== CREATE NODE ===================== */
adrNode createNode(int priority, string info) {
    adrNode p = new Node;
    p->priority = priority;
    p->info = info;
    p->left = nullptr;
    p->right = nullptr;
    return p;
}

/* ===================== INSERT ===================== */
adrNode insertNode(adrNode root, int priority, string info) {
    if (root == nullptr) {
        return createNode(priority, info);
    }

    if (priority < root->priority) {
        root->left = insertNode(root->left, priority, info);
    } else if (priority > root->priority) {
        root->right = insertNode(root->right, priority, info);
    } else {
        cout << "Priority sudah ada, data tidak dimasukkan.\n";
    }

    return root;
}

/* ===================== SEARCH ===================== */
adrNode searchNode(adrNode root, int priority) {
    if (root == nullptr || root->priority == priority) {
        return root;
    }

    if (priority < root->priority) {
        return searchNode(root->left, priority);
    }

    return searchNode(root->right, priority);
}

/* ===================== FIND MIN ===================== */
adrNode findMin(adrNode root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

/* ===================== DELETE ===================== */
adrNode deleteNode(adrNode root, int priority) {
    if (root == nullptr) {
        return nullptr;
    }

    if (priority < root->priority) {
        root->left = deleteNode(root->left, priority);
    } else if (priority > root->priority) {
        root->right = deleteNode(root->right, priority);
    } else {
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

/* ===================== SUCCESSOR ===================== */
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

/* ===================== PREDECESSOR ===================== */
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

/* ===================== INORDER ===================== */
void inorder(adrNode root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "Priority : " << root->priority
             << " | Info : " << root->info << endl;
        inorder(root->right);
    }
}

/* ===================== COUNT LEVEL ===================== */
int countAtLevel(adrNode root, int level) {
    if (root == nullptr) {
        return 0;
    }

    if (level == 0) {
        return 1;
    }

    return countAtLevel(root->left, level - 1)
         + countAtLevel(root->right, level - 1);
}

/* ===================== RANGE SEARCH ===================== */
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

/* ===================== PRINT TREE ===================== */
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
