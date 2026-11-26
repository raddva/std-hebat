#include"item.h"
#include "statistics.h"
#include "inventory.h"
#include"mod.h"
#include <iostream>

using namespace std;
int main() {
    srand(static_cast<unsigned int>(time(0)));

    ListPlayer LP;
    createListPlayer(LP);

    infotypePlayer p1Data = {"P01", "Steve", 20, 20};
    infotypePlayer p2Data = {"P02", "Alex", 18, 20};
    adrPlayer P1 = alokasiPlayer(p1Data);
    adrPlayer P2 = alokasiPlayer(p2Data);

    insertFirstPlayer(LP, P1);
    insertFirstPlayer(LP, P2);

    infotypeInventory inv1 = {"INV01", "Diamond Sword", "Weapon", 1, 0, 1, 12, 0};
    infotypeInventory inv2 = {"INV02", "Oak Planks", "Block", 64, 15, 100, 45, 2};
    infotypeInventory inv3 = {"INV03", "Grass Block", "Block", 32, 40, 0, 7, 1};

    adrInventory I1 = alokasiInventory(inv1);
    adrInventory I2 = alokasiInventory(inv2);
    adrInventory I3 = alokasiInventory(inv3);

    insertLastInventory(P1, I1);
    insertLastInventory(P1, I2);
    insertLastInventory(P1, I3);

    infotypeDetail d1 = {"D01", "Base Diamond Blade", 5, 1561, 7};
    infotypeDetail d2 = {"D02", "Enchantment: Sharpness II", 5, 1561, 3};
    infotypeDetail d3 = {"D03", "Building Material", 0, 0, 0};
    infotypeDetail d4 = {"D04", "Natural Terrain Block", 0, 0, 0};

    insertFirstDetail(I1, alokasiDetail(d1));
    insertFirstDetail(I1, alokasiDetail(d2));
    insertFirstDetail(I2, alokasiDetail(d3));
    insertFirstDetail(I3, alokasiDetail(d4));

    infotypeInventory inv4 = {"INV04", "Iron Pickaxe", "Tool", 1, 0, 2, 8, 0};
    adrInventory I4 = alokasiInventory(inv4);
    insertLastInventory(P2, I4);
    insertFirstDetail(I4, alokasiDetail({"D05", "Base Iron Head", 250, 250, 4}));

    int pilihan = -1;
    while (pilihan != 0) {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Show All Players, Inventory & Detail Item\n";
        cout << "2. Tambah Player\n";
        cout << "3. Tambah Item ke Inventory Player\n";
        cout << "4. Tambah Detail Item \n";
        cout << "5. Tambah Mobs\n";
        cout << "6. Craft / Mine Tambahan Stok Item\n";
        cout << "7. Heal Health Bar Player\n";
        cout << "8. Hapus Item dari Inventory Player\n";
        cout << "9. Hapus Player beserta Seluruh Inventory\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) {
            showAllData(LP);
        } else if (pilihan == 2) {
            infotypePlayer pBaru;
            cout << "ID Player       : "; cin >> pBaru.idPlayer;
            cout << "Username        : "; cin >> pBaru.username;
            cout << "Max Health (HP) : "; cin >> pBaru.maxHealth;
            pBaru.health = pBaru.maxHealth;
            insertFirstPlayer(LP, alokasiPlayer(pBaru));
            cout << "Player berhasil ditambahkan!\n";
        } else if (pilihan == 3) {
            string idP;
            cout << "Masukkan ID Player tujuan: "; cin >> idP;
            adrPlayer targetP = searchPlayer(LP, idP);
            if (targetP != nullptr) {
                infotypeInventory invBaru;
                cout << "ID Inventory               : "; cin >> invBaru.idInv;
                cout << "Nama Item (tanpa spasi)    : "; cin >> invBaru.namaItem;
                cout << "Kategori (Block/Weapon/Tool): "; cin >> invBaru.kategori;
                cout << "Jumlah awal                : "; cin >> invBaru.jumlah;
                invBaru.timesMined = 0;
                invBaru.timesCrafted = 1;
                invBaru.timesUsed = 0;
                invBaru.timesDropped = 0;
                insertLastInventory(targetP, alokasiInventory(invBaru));
                cout << "Item berhasil ditambahkan ke inventory " << targetP->info.username << "!\n";
            } else {
                cout << "Player tidak ditemukan!\n";
            }
        } else if (pilihan == 4) {
            string idP, idI;
            cout << "Masukkan ID Player    : "; cin >> idP;
            adrPlayer targetP = searchPlayer(LP, idP);
            if (targetP != nullptr) {
                cout << "Masukkan ID Inventory : "; cin >> idI;
                adrInventory targetI = searchInventory(targetP, idI);
                if (targetI != nullptr) {
                    infotypeDetail detBaru;
                    cout << "ID Detail                   : "; cin >> detBaru.idDetail;
                    cout << "Nama Atribut (tanpa spasi)  : "; cin >> detBaru.namaAtribut;
                    cout << "Max Durability (0 jika Block): "; cin >> detBaru.maxDurability;
                    detBaru.durability = detBaru.maxDurability;
                    cout << "Poin Damage                 : "; cin >> detBaru.damage;
                    insertFirstDetail(targetI, alokasiDetail(detBaru));
                    cout << "Detail item berhasil ditambahkan!\n";
                } else {
                    cout << "Inventory tidak ditemukan!\n";
                }
            } else {
                cout << "Player tidak ditemukan!\n";
            }
        } else if (pilihan == 5) {
            string idAtk, idTgt, idI;
            cout << "ID Player Pengguna Item              : "; cin >> idAtk;
            cout << "ID Player Target (isi '-' jika Block): "; cin >> idTgt;
            cout << "ID Inventory Item yang digunakan     : "; cin >> idI;
            useOrAttackItem(LP, idAtk, idTgt, idI);
        } else if (pilihan == 6) {
            string idP, idI;
            int qty, mode;
            cout << "ID Player   : "; cin >> idP;
            cout << "ID Inventory: "; cin >> idI;
            cout << "Jumlah      : "; cin >> qty;
            cout << "Sumber (1 = Crafted, 0 = Mined): "; cin >> mode;
            tambahStokItem(LP, idP, idI, qty, (mode == 1));
        } else if (pilihan == 7) {
            string idP;
            int hp;
            cout << "ID Player        : "; cin >> idP;
            cout << "Jumlah Heal (HP) : "; cin >> hp;
            healPlayer(LP, idP, hp);
        } else if (pilihan == 8) {
            string idP, idI;
            cout << "ID Player   : "; cin >> idP;
            adrPlayer targetP = searchPlayer(LP, idP);
            if (targetP != nullptr) {
                cout << "ID Inventory yang dihapus: "; cin >> idI;
                deleteInventoryByID(targetP, idI);
                cout << "Proses penghapusan item selesai.\n";
            } else {
                cout << "Player tidak ditemukan!\n";
            }
        } else if (pilihan == 9) {
            string idP;
            cout << "ID Player yang dihapus: "; cin >> idP;
            deletePlayerByID(LP, idP);
            cout << "Proses penghapusan player selesai.\n";
        } else if (pilihan == 0) {
            cout << "Keluar dari program.\n";
        } else {
            cout << "Pilihan menu tidak valid.\n";
        }
    }

    return 0;
}
