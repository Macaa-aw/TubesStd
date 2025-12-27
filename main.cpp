#include "header.h"
using namespace std;

int main() {
    adrNode root = nullptr;
    int pilih = -1;

    while (pilih != 0) {
        cout << "\n=== SISTEM MANAJEMEN PRIORITAS DARURAT (BST) ===\n";
        cout << "1. Insert Kasus\n";
        cout << "2. Delete Kasus\n";
        cout << "3. Search Kasus\n";
        cout << "4. Tampilkan Inorder\n";
        cout << "5. Cari Successor\n";
        cout << "6. Cari Predecessor\n";
        cout << "7. Hitung Node Pada Level\n";
        cout << "8. Cari Berdasarkan Range Prioritas\n";
        cout << "9. Print Tree\n";
        cout << "10. Cek Tinggi Tree\n";
        cout << "11. Cek Keseimbangan Tree\n";
        cout << "12. Hapus Semua Tree\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilih;

        if (pilih == 1) {
            int pr;
            string info;
            cout << "Priority : ";
            cin >> pr;
            cin.ignore();
            cout << "Info     : ";
            getline(cin, info);
            root = insertNode(root, pr, info);
        }

        else if (pilih == 2) {
            int pr;
            cout << "Priority yang dihapus: ";
            cin >> pr;
            root = deleteNode(root, pr);
        }

        else if (pilih == 3) {
            int pr;
            cout << "Priority dicari: ";
            cin >> pr;
            adrNode hasil = searchNode(root, pr);

            if (hasil != nullptr)
                cout << "Ditemukan: " << hasil->info << endl;
            else
                cout << "Data tidak ditemukan\n";
        }

        else if (pilih == 4) {
            cout << "\n=== INORDER TRAVERSAL ===\n";
            inorder(root);
        }

        else if (pilih == 5) {
            int pr;
            cout << "Priority: ";
            cin >> pr;
            adrNode s = findSuccessor(root, pr);

            if (s != nullptr)
                cout << "Successor: " << s->priority << " - " << s->info << endl;
            else
                cout << "Tidak ada successor\n";
        }

        else if (pilih == 6) {
            int pr;
            cout << "Priority: ";
            cin >> pr;
            adrNode p = findPredecessor(root, pr);

            if (p != nullptr)
                cout << "Predecessor: " << p->priority << " - " << p->info << endl;
            else
                cout << "Tidak ada predecessor\n";
        }

        else if (pilih == 7) {
            int lvl;
            cout << "Level: ";
            cin >> lvl;
            cout << "Jumlah node pada level " << lvl
                 << " = " << countAtLevel(root, lvl) << endl;
        }

        else if (pilih == 8) {
            int low, high;
            cout << "Range rendah  : ";
            cin >> low;
            cout << "Range tinggi  : ";
            cin >> high;
            cout << "\nData dalam range:\n";
            searchRange(root, low, high);
        }

        else if (pilih == 9) {
            cout << "\n=== STRUKTUR TREE ===\n";
            printTree(root, 0, 6);
        }

        else if (pilih == 10) {
            cout << "Tinggi Tree = " << height(root) << endl;
        }

        else if (pilih == 11) {
            if (isBalanced(root))
                cout << "Tree Seimbang\n";
            else
                cout << "Tree Tidak Seimbang\n";
        }

        else if (pilih == 12) {
            clearTree(root);
            cout << "SEMUA DATA TREE BERHASIL DIHAPUS!\n";
        }

        else if (pilih == 0) {
            clearTree(root);
            cout << "Keluar...\n";
        }

        else {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}

