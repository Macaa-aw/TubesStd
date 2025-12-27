#include "header.h"

/* ===================== CREATE NODE ===================== */
/* I.S : Belum ada node baru, data priority dan info tersedia
   F.S : Node baru terbentuk dengan priority dan info,
         left dan right bernilai nullptr */
adrNode createNode(int priority, string info) {
    adrNode p = new Node;
    p->priority = priority;
    p->info = info;
    p->left = nullptr;
    p->right = nullptr;
    return p;
}

/* ===================== INSERT ===================== */
/* I.S : Tree mungkin kosong atau sudah berisi node
   F.S : Node baru ditambahkan sesuai aturan BST */
adrNode insertNode(adrNode root, int priority, string info) {
    if (root == nullptr)
        return createNode(priority, info);

    if (priority < root->priority)
        root->left = insertNode(root->left, priority, info);
    else if (priority > root->priority)
        root->right = insertNode(root->right, priority, info);
    else
        cout << "Priority sudah ada, data tidak dimasukkan.\n";

    return root;
}

/* ===================== SEARCH ===================== */
/* I.S : Tree berisi data
   F.S : Mengembalikan alamat node jika ditemukan,
         atau nullptr jika tidak ditemukan */
adrNode searchNode(adrNode root, int priority) {
    if (root == nullptr || root->priority == priority)
        return root;

    if (priority < root->priority)
        return searchNode(root->left, priority);
    return searchNode(root->right, priority);
}

/* ===================== FIND MIN ===================== */
/* I.S : Tree tidak kosong
   F.S : Mengembalikan node dengan priority terkecil */
adrNode findMin(adrNode root) {
    while (root && root->left != nullptr)
        root = root->left;
    return root;
}

/* ===================== DELETE ===================== */
/* I.S : Tree berisi data
   F.S : Node dengan priority tertentu dihapus dari tree */
adrNode deleteNode(adrNode root, int priority) {
    if (root == nullptr)
        return nullptr;

    if (priority < root->priority)
        root->left = deleteNode(root->left, priority);
    else if (priority > root->priority)
        root->right = deleteNode(root->right, priority);
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

/* ===================== SUCCESSOR ===================== */
/* I.S : Tree berisi data
   F.S : Mengembalikan node successor dari priority tertentu */
adrNode findSuccessor(adrNode root, int priority) {
    adrNode succ = nullptr;
    while (root != nullptr) {
        if (priority < root->priority) {
            succ = root;
            root = root->left;
        } else
            root = root->right;
    }
    return succ;
}

/* ===================== PREDECESSOR ===================== */
/* I.S : Tree berisi data
   F.S : Mengembalikan node predecessor dari priority tertentu */
adrNode findPredecessor(adrNode root, int priority) {
    adrNode pred = nullptr;
    while (root != nullptr) {
        if (priority > root->priority) {
            pred = root;
            root = root->right;
        } else
            root = root->left;
    }
    return pred;
}

/* ===================== TRAVERSAL ===================== */
/* I.S : Tree berisi data
   F.S : Data ditampilkan secara inorder */
void inorder(adrNode root){
    if(root != nullptr){
        inorder(root->left);
        cout << "Priority: " << root->priority
             << " | Info: " << root->info << endl;
        inorder(root->right);
    }
}

/* I.S : Tree berisi data
   F.S : Data ditampilkan secara preorder */
void preorder(adrNode root){
    if(root != nullptr){
        cout << root->priority << " - " << root->info << endl;
        preorder(root->left);
        preorder(root->right);
    }
}

/* I.S : Tree berisi data
   F.S : Data ditampilkan secara postorder */
void postorder(adrNode root){
    if(root != nullptr){
        postorder(root->left);
        postorder(root->right);
        cout << root->priority << " - " << root->info << endl;
    }
}

/* ===================== LEVEL COUNT ===================== */
/* I.S : Tree berisi data dan level diketahui
   F.S : Mengembalikan jumlah node pada level tertentu */
int countAtLevel(adrNode root, int level){
    if(root == nullptr)
        return 0;
    if(level == 0)
        return 1;
    return countAtLevel(root->left, level-1)
         + countAtLevel(root->right, level-1);
}

/* ===================== RANGE ===================== */
/* I.S : Tree berisi data dan batas range diketahui
   F.S : Menampilkan node yang berada dalam range */
void searchRange(adrNode root, int low, int high){
    if(root == nullptr)
        return;

    if(low < root->priority)
        searchRange(root->left, low, high);

    if(low <= root->priority && root->priority <= high)
        cout << root->priority << " - " << root->info << endl;

    if(high > root->priority)
        searchRange(root->right, low, high);
}

/* ===================== PRINT TREE ===================== */
/* I.S : Tree berisi data
   F.S : Tree ditampilkan secara visual ke layar */
void printTree(adrNode root, int space, int gap){
    if(root == nullptr)
        return;

    space += gap;

    printTree(root->right, space, gap);

    cout << endl;
    for(int i = gap; i < space; i++)
        cout << " ";
    cout << "[" << root->priority << "] " << root->info << endl;

    printTree(root->left, space, gap);
}

/* ===================== HEIGHT ===================== */
/* I.S : Tree berisi data
   F.S : Mengembalikan tinggi tree */
int height(adrNode root){
    if (root == nullptr){
        return -1;
    }

    int leftHeight  = height(root->left);
    int rightHeight = height(root->right);

    int result;
    if(leftHeight > rightHeight){
        result = leftHeight;
    } else {
        result = rightHeight;
    }

    return result + 1;
}

/* ===================== BALANCE ===================== */\
/* I.S : Tree berisi data
   F.S : Mengembalikan true jika tree seimbang */
bool isBalanced(adrNode root){
    if(root == nullptr)
        return true;

    int lh = height(root->left);
    int rh = height(root->right);

    if(lh - rh > 1 || rh - lh > 1)
        return false;

    return isBalanced(root->left) && isBalanced(root->right);
}

/* ===================== CLEAR ===================== */
/* I.S : Tree berisi data
   F.S : Seluruh node dihapus dan root menjadi nullptr */
void clearTree(adrNode &root){
    if(root != nullptr){
        clearTree(root->left);
        clearTree(root->right);
        delete root;
        root = nullptr;
    }
}

