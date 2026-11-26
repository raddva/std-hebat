#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include "inventory.h"
#include "statistics.h"
#include <string>

using namespace std; 

typedef struct elmItem *adrItem;

struct itemInfo {
    string itemName;
    string itemClass;
    int maxStack; 
}

struct elmItemStats{ 
    itemInfo info; 
    adrItem next;
    adrItem prev; 

}

struct listItem {
    adrItem first;
    adrItem last;
};

void addMaxStack(itemInfo &info);
void createListItem(listItem &LI);
adrItem alokasiItem(itemInfo data);
void insertFirstItem(listItem &LI, adrItem P);
void insertlastItem(listItem &LI, adrItem p);
adrItem searchItem(listItem &LI, adrItem p, string Iditem);

#endif