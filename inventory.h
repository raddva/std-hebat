#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef struct elmPlayer *adrPlayer;
typedef struct elmInventory *adrInventory;
typedef struct elmDetail *adrDetail;

struct infotypeDetail {
    string idDetail;
    string namaAtribut;
    int durability;
    int maxDurability;
    int damage;
};

struct elmDetail {
    infotypeDetail info;
    adrDetail next;
};

struct ListDetail {
    adrDetail first;
};

struct infotypeInventory {
    string idInv;
    string namaItem;
    string kategori;
    int jumlah;
    int timesMined;
    int timesCrafted;
    int timesUsed;
    int timesDropped;
};

struct elmInventory {
    infotypeInventory info;
    adrDetail firstDetail;
    adrInventory next;
};

struct ListInventory {
    adrInventory first;
};

struct infotypePlayer {
    string idPlayer;
    string username;
    int health;
    int maxHealth;
};

struct elmPlayer {
    infotypePlayer info;
    adrInventory firstInv;
    adrPlayer next;
};

struct ListPlayer {
    adrPlayer first;
};


/* I.S. Sembarang
   F.S. Terbentuk ListPlayer kosong (LP.first = nullptr) */
void createListPlayer(ListPlayer &LP);

/* I.S. Sembarang
   F.S. Terbentuk ListInventory kosong (LI.first = nullptr) */
void createListInventory(ListInventory &LI);

/* I.S. Sembarang
   F.S. Terbentuk ListDetail kosong (LD.first = nullptr) */
void createListDetail(ListDetail &LD);

/* I.S. Data player terdefinisi
   F.S. Mengembalikan alamat elemen Player baru dengan firstInv = nullptr dan next = nullptr */
adrPlayer alokasiPlayer(infotypePlayer data);

/* I.S. Data inventory terdefinisi
   F.S. Mengembalikan alamat elemen Inventory baru dengan firstDetail = nullptr dan next = nullptr */
adrInventory alokasiInventory(infotypeInventory data);

/* I.S. Data detail item terdefinisi
   F.S. Mengembalikan alamat elemen Detail baru dengan next = nullptr */
adrDetail alokasiDetail(infotypeDetail data);

/* I.S. ListPlayer terdefinisi (mungkin kosong), P adalah alamat elemen Player baru
   F.S. Elemen P ditambahkan sebagai elemen pertama pada ListPlayer (Insert First) */
void insertFirstPlayer(ListPlayer &LP, adrPlayer P);

/* I.S. P adalah alamat elemen Player yang valid, I adalah alamat elemen Inventory baru
   F.S. Elemen I ditambahkan sebagai elemen terakhir pada inventory milik P (Insert Last) */
void insertLastInventory(adrPlayer P, adrInventory I);

/* I.S. I adalah alamat elemen Inventory yang valid, D adalah alamat elemen Detail baru
   F.S. Elemen D ditambahkan sebagai elemen pertama pada detail milik I (Insert First) */
void insertFirstDetail(adrInventory I, adrDetail D);

/* I.S. ListPlayer terdefinisi, idPlayer terdefinisi
   F.S. Mengembalikan alamat elemen Player jika ditemukan, atau nullptr jika tidak ditemukan */
adrPlayer searchPlayer(ListPlayer LP, string idPlayer);

/* I.S. P adalah alamat elemen Player yang valid, idInv terdefinisi
   F.S. Mengembalikan alamat elemen Inventory milik P jika ditemukan, atau nullptr jika tidak */
adrInventory searchInventory(adrPlayer P, string idInv);

/* I.S. I adalah alamat elemen Inventory yang valid, idDetail terdefinisi
   F.S. Mengembalikan alamat elemen Detail milik I jika ditemukan, atau nullptr jika tidak */
adrDetail searchDetail(adrInventory I, string idDetail);

/* I.S. I adalah alamat elemen Inventory yang valid
   F.S. Seluruh elemen Detail pada I dihapus dan didealokasi (I->firstDetail = nullptr) */
void deleteAllDetail(adrInventory I);

/* I.S. P adalah alamat elemen Player yang valid
   F.S. Elemen pertama pada inventory milik P dihapus beserta seluruh detailnya (Delete First) */
void deleteFirstInventory(adrPlayer P, adrInventory &I);

/* I.S. P adalah alamat elemen Player yang valid, idInv terdefinisi
   F.S. Elemen inventory dengan idInv dihapus dari P beserta seluruh detailnya jika ditemukan */
void deleteInventoryByID(adrPlayer P, string idInv);

/* I.S. ListPlayer terdefinisi, idPlayer terdefinisi
   F.S. Elemen Player dengan idPlayer dihapus beserta seluruh inventory dan detailnya */
void deletePlayerByID(ListPlayer &LP, string idPlayer);

/* I.S. Health saat ini dan maksimal terdefinisi
   F.S. Menampilkan visualisasi Health Bar di layar */
void printHealthBar(int health, int maxHealth);

/* I.S. ListPlayer terdefinisi (mungkin kosong)
   F.S. Menampilkan seluruh data Player, Inventory (statistik item), dan Detail Item */
void showAllData(ListPlayer LP);

/* I.S. P adalah alamat elemen Player yang valid
   F.S. Mengembalikan total akumulasi damage dari seluruh item yang dimiliki Player P */
int hitungTotalDamagePlayer(adrPlayer P);

/* I.S. ListPlayer terdefinisi, idAttacker, idTarget, dan idInv terdefinisi
   F.S. Attacker menggunakan item idInv (timesUsed bertambah, durability berkurang).
        Jika item tipe Weapon/Tool, health Target berkurang sesuai damage.
        Jika item tipe Block, jumlah berkurang 1. Item otomatis terhapus jika rusak/habis. */
void useOrAttackItem(ListPlayer &LP, string idAttacker, string idTarget, string idInv);

/* I.S. ListPlayer terdefinisi, idPlayer dan idInv terdefinisi
   F.S. Menambahkan jumlah item sebanyak qty dan menambah statistik timesCrafted atau timesMined */
void tambahStokItem(ListPlayer &LP, string idPlayer, string idInv, int qty, bool isCrafted);

/* I.S. ListPlayer terdefinisi, idPlayer dan healPoint terdefinisi
   F.S. Menambah health Player sebesar healPoint tanpa melebihi maxHealth */
void healPlayer(ListPlayer &LP, string idPlayer, int healPoint);

#endif // INVENTORY_H_INCLUDED
