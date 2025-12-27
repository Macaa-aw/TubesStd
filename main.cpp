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
                cout << "Info     : ";
                cin >> info;
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
                    cout << "Successor: " << s->priority << " - " << s->info << endl;
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
                    cout << "Predecessor: " << p->priority << " - " << p->info << endl;
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

            case 8: {
                int low, high;
                cout << "Range rendah: ";
                cin >> low;
                cout << "Range tinggi: ";
                cin >> high;
                searchRange(root, low, high);
                break;
            }

            case 9: {
                cout << "\n=== STRUKTUR TREE (90 Derajat) ===\n" << endl;
                printTree(root, 0, 5);  // gap = 5 spasi per level
                cout << endl;
                break;
            }
        }
    }

    return 0;
}

