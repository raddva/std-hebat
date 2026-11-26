#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include "inventory.h"
#include "statistics.h"
#include <string>

using namespace std; 

typedef struct elmPlayer *adrPlayer;

struct playerInfo {
    string playerName;
    string account;
    string password; 
    // inventory
    // mobs
    // stats
    //
}

struct elmPlayerStats{ 
    playerInfo info; 
    adrPlayer next;
    adrPlayer prev; 

}

struct listPlayer {
    adrPlayer first;
    adrPlayer last;
};

void addMaxStack(playerInfo &info);
void createListPlayer(listPlayer &LI);
adrPlayer alokasiPlayer(PlayerInfo data);
void insertFirstPlayer(listPlayer &LI, adrPlayer P);
void insertlastPlayer(listPlayer &LI, adrPlayer p);
adrPlayer searchPlayer(listPlayer &LI, adrPlayer p, string playerName);

#endif