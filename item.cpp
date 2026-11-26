#include "item.h"
#include "statistics.h"
#include "inventory.h"
#include <iostream>
#include <string>

using namespace std;

void addMaxStack(itemInfo &I){
    if (I.itemClass == "Utilities" || I.itemClass == "Armor"){
        I.maxStack = 1;
    } else if (I.itemClass == "Block"){
        I.maxStack = 64;
    } else if (I.itemClass == "Ingredients"){
        I.maxStack = 16;
    }
}

void createListItem(listItem &LI){
    LI.first = nullptr;
    LI.last = nullptr;
}

adrItem alokasiItem(itemInfo data){
    adrItem p = new elmItem;
    p->info.itemName  = data.itemName;
    p->info.itemClass = data.itemClass;
    p->info.maxStack  = data.maxStack;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void insertFirstItem(listItem &LI, adrItem p){
    if (LI.first == nullptr){
        LI.first = p;
        LI.last = p;
    } else {
        p->next = LI.first;
        LI.first->prev = p;
        LI.first = p;
    }
}

void insertLastItem(listItem &LI, adrItem p){
    if (LI.last == nullptr){
        LI.first = p;
        LI.last = p;
    } else {
        p->prev = LI.last;
        LI.last->next = p;
        LI.last = p;
    }
}

adrItem searchItem(listItem LI, string idItem){
    adrItem p = LI.first;
    while (p != nullptr){
        if (p->info.itemName == idItem){
            return p;
        }
        p = p->next;
    }
    return nullptr;
}