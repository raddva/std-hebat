#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <iostream>
#include <string>

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
    int tMined;
    int tCrafted;
    int tUsed;
    int tDropped;
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

void createListPlayer(ListPlayer &LP);

void createListInventory(ListInventory &LI);

void createListDetail(ListDetail &LD);

adrPlayer alokasiPlayer(infotypePlayer data);

adrInventory alokasiInventory(infotypeInventory data);

adrDetail alokasiDetail(infotypeDetail data);

void insertFirstPlayer(ListPlayer &LP, adrPlayer P);

void insertLastInventory(adrPlayer P, adrInventory I);

void insertFirstDetail(adrInventory I, adrDetail D);

adrPlayer searchPlayer(ListPlayer LP, string idPlayer);

adrInventory searchInventory(adrPlayer P, string idInv);

adrDetail searchDetail(adrInventory I, string idDetail);

void deleteAllDetail(adrInventory I);

void deleteFirstInventory(adrPlayer P, adrInventory &I);

void deleteInventoryByID(adrPlayer P, string idInv);

void deletePlayerByID(ListPlayer &LP, string idPlayer);

void printHealthBar(int health, int maxHealth);

void showAllData(ListPlayer LP);

int hitungTotalDamagePlayer(adrPlayer P);

void useOrAttackItem(ListPlayer &LP, string idAttacker, string idTarget, string idInv);

void tambahStokItem(ListPlayer &LP, string idPlayer, string idInv, int qty, bool isCrafted);

void healPlayer(ListPlayer &LP, string idPlayer, int healPoint);


#endif 
// INVENTORY_H_INCLUDED
