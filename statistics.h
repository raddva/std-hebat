#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include <iostream>
#include "inventory.h"
#include "item.h"
#include <string>

using namespace std; 

typedef struct elmItemStats *adrItemStats;
typedef struct elmMobStats *adrMob;  

struct itemStats {
    string itemName; 
    int tMined;
    int tBroken; 
    int tCrafted; 
    int tUsed; 
    int tPickup; 
    int tDropped; 
}

struct mobStats {
    string mobName;
    int tKill; 
    int tDeath; 
}

struct elmItemStats{ 
    itemStats info; 
    adrItemStats next;
    adrItemStats prev; 
}

struct listMob {
    adrItem first;
    adrItem last;
};

void createListMob(listMob &LI);
adrMob alokasiMob(mobInfo data);
void insertFirstMob(listMob &LI, adrMob P);
void insertlastMob(listMob &LI, adrMob p);
adrMob searchItem(listMob &LI, adrMob p, string mobName );

#endif