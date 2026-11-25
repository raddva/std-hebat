#include "inventory.h"

/* I.S. Sembarang
   F.S. Terbentuk ListPlayer kosong (LP.first = nullptr) */
void createListPlayer(ListPlayer &LP) {
    LP.first = nullptr;
}

/* I.S. Sembarang
   F.S. Terbentuk ListInventory kosong (LI.first = nullptr) */
void createListInventory(ListInventory &LI) {
    LI.first = nullptr;
}

/* I.S. Sembarang
   F.S. Terbentuk ListDetail kosong (LD.first = nullptr) */
void createListDetail(ListDetail &LD) {
    LD.first = nullptr;
}

/* I.S. Data player terdefinisi
   F.S. Mengembalikan alamat elemen Player baru dengan firstInv = nullptr dan next = nullptr */
adrPlayer alokasiPlayer(infotypePlayer data) {
    adrPlayer P = new elmPlayer;
    P->info = data;
    P->firstInv = nullptr;
    P->next = nullptr;
    return P;
}

/* I.S. Data inventory terdefinisi
   F.S. Mengembalikan alamat elemen Inventory baru dengan firstDetail = nullptr dan next = nullptr */
adrInventory alokasiInventory(infotypeInventory data) {
    adrInventory I = new elmInventory;
    I->info = data;
    I->firstDetail = nullptr;
    I->next = nullptr;
    return I;
}

/* I.S. Data detail item terdefinisi
   F.S. Mengembalikan alamat elemen Detail baru dengan next = nullptr */
adrDetail alokasiDetail(infotypeDetail data) {
    adrDetail D = new elmDetail;
    D->info = data;
    D->next = nullptr;
    return D;
}

/* I.S. ListPlayer terdefinisi (mungkin kosong), P adalah alamat elemen Player baru
   F.S. Elemen P ditambahkan sebagai elemen pertama pada ListPlayer (Insert First) */
void insertFirstPlayer(ListPlayer &LP, adrPlayer P) {
    if (P != nullptr) {
        P->next = LP.first;
        LP.first = P;
    }
}

/* I.S. P adalah alamat elemen Player yang valid, I adalah alamat elemen Inventory baru
   F.S. Elemen I ditambahkan sebagai elemen terakhir pada inventory milik P (Insert Last) */
void insertLastInventory(adrPlayer P, adrInventory I) {
    if (P != nullptr && I != nullptr) {
        if (P->firstInv == nullptr) {
            P->firstInv = I;
        } else {
            adrInventory Q = P->firstInv;
            while (Q->next != nullptr) {
                Q = Q->next;
            }
            Q->next = I;
        }
    }
}

/* I.S. I adalah alamat elemen Inventory yang valid, D adalah alamat elemen Detail baru
   F.S. Elemen D ditambahkan sebagai elemen pertama pada detail milik I (Insert First) */
void insertFirstDetail(adrInventory I, adrDetail D) {
    if (I != nullptr && D != nullptr) {
        D->next = I->firstDetail;
        I->firstDetail = D;
    }
}

/* I.S. ListPlayer terdefinisi, idPlayer terdefinisi
   F.S. Mengembalikan alamat elemen Player jika ditemukan, atau nullptr jika tidak ditemukan */
adrPlayer searchPlayer(ListPlayer LP, string idPlayer) {
    adrPlayer P = LP.first;
    adrPlayer foundPlayer = nullptr;

    while (P != nullptr && foundPlayer == nullptr) {
        if (P->info.idPlayer == idPlayer) {
            foundPlayer = P;
        } else {
            P = P->next;
        }
    }
    return foundPlayer;
}

/* I.S. P adalah alamat elemen Player yang valid, idInv terdefinisi
   F.S. Mengembalikan alamat elemen Inventory milik P jika ditemukan, atau nullptr jika tidak */
adrInventory searchInventory(adrPlayer P, string idInv) {
    adrInventory foundInv = nullptr;
    if (P != nullptr) {
        adrInventory I = P->firstInv;
        while (I != nullptr && foundInv == nullptr) {
            if (I->info.idInv == idInv) {
                foundInv = I;
            } else {
                I = I->next;
            }
        }
    }
    return foundInv;
}

/* I.S. I adalah alamat elemen Inventory yang valid, idDetail terdefinisi
   F.S. Mengembalikan alamat elemen Detail milik I jika ditemukan, atau nullptr jika tidak */
adrDetail searchDetail(adrInventory I, string idDetail) {
    adrDetail foundDet = nullptr;
    if (I != nullptr) {
        adrDetail D = I->firstDetail;
        while (D != nullptr && foundDet == nullptr) {
            if (D->info.idDetail == idDetail) {
                foundDet = D;
            } else {
                D = D->next;
            }
        }
    }
    return foundDet;
}

/* I.S. I adalah alamat elemen Inventory yang valid
   F.S. Seluruh elemen Detail pada I dihapus dan didealokasi (I->firstDetail = nullptr) */
void deleteAllDetail(adrInventory I) {
    if (I != nullptr) {
        adrDetail D = I->firstDetail;
        adrDetail temp;
        while (D != nullptr) {
            temp = D;
            D = D->next;
            delete temp;
        }
        I->firstDetail = nullptr;
    }
}

/* I.S. P adalah alamat elemen Player yang valid
   F.S. Elemen pertama pada inventory milik P dihapus beserta seluruh detailnya (Delete First) */
void deleteFirstInventory(adrPlayer P, adrInventory &I) {
    I = nullptr;
    if (P != nullptr && P->firstInv != nullptr) {
        I = P->firstInv;
        P->firstInv = I->next;
        I->next = nullptr;
        deleteAllDetail(I);
        delete I;
        I = nullptr;
    }
}

/* I.S. P adalah alamat elemen Player yang valid, idInv terdefinisi
   F.S. Elemen inventory dengan idInv dihapus dari P beserta seluruh detailnya jika ditemukan */
void deleteInventoryByID(adrPlayer P, string idInv) {
    if (P != nullptr && P->firstInv != nullptr) {
        adrInventory curr = P->firstInv;
        adrInventory prev = nullptr;
        bool found = false;

        while (curr != nullptr && !found) {
            if (curr->info.idInv == idInv) {
                found = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        if (found) {
            if (prev == nullptr) {
                adrInventory temp;
                deleteFirstInventory(P, temp);
            } else {
                prev->next = curr->next;
                curr->next = nullptr;
                deleteAllDetail(curr);
                delete curr;
            }
        }
    }
}

/* I.S. ListPlayer terdefinisi, idPlayer terdefinisi
   F.S. Elemen Player dengan idPlayer dihapus beserta seluruh inventory dan detailnya */
void deletePlayerByID(ListPlayer &LP, string idPlayer) {
    if (LP.first != nullptr) {
        adrPlayer curr = LP.first;
        adrPlayer prev = nullptr;
        bool found = false;

        while (curr != nullptr && !found) {
            if (curr->info.idPlayer == idPlayer) {
                found = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        if (found) {
            adrInventory tempInv;
            while (curr->firstInv != nullptr) {
                deleteFirstInventory(curr, tempInv);
            }

            if (prev == nullptr) {
                LP.first = curr->next;
            } else {
                prev->next = curr->next;
            }
            curr->next = nullptr;
            delete curr;
        }
    }
}

/* I.S. Health saat ini dan maksimal terdefinisi
   F.S. Menampilkan visualisasi Health Bar di layar */
void printHealthBar(int health, int maxHealth) {
    int totalBar = 10;
    int filled = 0;
    if (maxHealth > 0) {
        filled = (health * totalBar) / maxHealth;
    }
    cout << "[";
    int i = 0;
    while (i < totalBar) {
        if (i < filled) {
            cout << "#";
        } else {
            cout << "-";
        }
        i++;
    }
    cout << "] " << health << "/" << maxHealth << " HP";
}

/* I.S. ListPlayer terdefinisi (mungkin kosong)
   F.S. Menampilkan seluruh data Player, Inventory (statistik item), dan Detail Item */
void showAllData(ListPlayer LP) {
    cout << "\n====================================================================\n";
    cout << "                  INVENTORY & STATISTICS                              \n";
    cout << "====================================================================\n";

    if (LP.first == nullptr) {
        cout << "Belum ada data Player yang terdaftar.\n";
    } else {
        adrPlayer P = LP.first;
        while (P != nullptr) {
            cout << "\n[PLAYER] ID: " << P->info.idPlayer
                 << " | Username: " << P->info.username << "\n";
            cout << "         Health  : ";
            printHealthBar(P->info.health, P->info.maxHealth);
            cout << " | Total Damage: " << hitungTotalDamagePlayer(P) << "\n";

            if (P->firstInv == nullptr) {
                cout << "   -> Inventory kosong.\n";
            } else {
                adrInventory I = P->firstInv;
                while (I != nullptr) {
                    cout << "   +--- [ITEM] (" << I->info.idInv << ") " << I->info.namaItem
                         << " [" << I->info.kategori << "] x" << I->info.jumlah << "\n";
                    cout << "   |    Stats -> Mined: " << I->info.timesMined
                         << " | Crafted: " << I->info.timesCrafted
                         << " | Used: " << I->info.timesUsed
                         << " | Dropped: " << I->info.timesDropped << "\n";

                    if (I->firstDetail == nullptr) {
                        cout << "   |      * Tidak ada detail atribut khusus.\n";
                    } else {
                        adrDetail D = I->firstDetail;
                        while (D != nullptr) {
                            cout << "   |      * [" << D->info.idDetail << "] " << D->info.namaAtribut
                                 << " | Durability: " << D->info.durability << "/" << D->info.maxDurability
                                 << " | Damage: +" << D->info.damage << "\n";
                            D = D->next;
                        }
                    }
                    I = I->next;
                }
            }
            cout << "--------------------------------------------------------------------\n";
            P = P->next;
        }
    }
}

/* I.S. P adalah alamat elemen Player yang valid
   F.S. Mengembalikan total akumulasi damage dari seluruh item yang dimiliki Player P */
int hitungTotalDamagePlayer(adrPlayer P) {
    int totalDamage = 0;
    if (P != nullptr) {
        adrInventory I = P->firstInv;
        while (I != nullptr) {
            adrDetail D = I->firstDetail;
            while (D != nullptr) {
                totalDamage = totalDamage + D->info.damage;
                D = D->next;
            }
            I = I->next;
        }
    }
    return totalDamage;
}

/* I.S. ListPlayer terdefinisi, idAttacker, idTarget, dan idInv terdefinisi
   F.S. Attacker menggunakan item idInv (timesUsed bertambah, durability berkurang).
        Jika item tipe Weapon/Tool, health Target berkurang sesuai damage.
        Jika item tipe Block, jumlah berkurang 1. Item otomatis terhapus jika rusak/habis. */
void useOrAttackItem(ListPlayer &LP, string idAttacker, string idTarget, string idInv) {
    adrPlayer attacker = searchPlayer(LP, idAttacker);
    if (attacker == nullptr) {
        cout << "Player pengguna tidak ditemukan!\n";
    } else {
        adrInventory item = searchInventory(attacker, idInv);
        if (item == nullptr) {
            cout << "Item tidak ditemukan di inventory " << attacker->info.username << "!\n";
        } else {
            item->info.timesUsed = item->info.timesUsed + 1;
            cout << attacker->info.username << " menggunakan " << item->info.namaItem
                 << " (Total Used: " << item->info.timesUsed << ").\n";

            if (item->info.kategori == "Block") {
                item->info.jumlah = item->info.jumlah - 1;
                cout << "Blok ditempatkan! Sisa stok: " << item->info.jumlah << "\n";
                if (item->info.jumlah <= 0) {
                    cout << item->info.namaItem << " habis dan dihapus dari inventory.\n";
                    deleteInventoryByID(attacker, idInv);
                }
            } else {
                int itemDamage = 0;
                bool itemBroken = false;
                adrDetail D = item->firstDetail;

                while (D != nullptr) {
                    itemDamage = itemDamage + D->info.damage;
                    if (D->info.maxDurability > 0) {
                        D->info.durability = D->info.durability - 1;
                        if (D->info.durability <= 0) {
                            D->info.durability = 0;
                            itemBroken = true;
                        }
                    }
                    D = D->next;
                }

                adrPlayer target = searchPlayer(LP, idTarget);
                if (target != nullptr && target != attacker) {
                    int critBonus = 0;
                    if ((rand() % 10) == 0) {
                        critBonus = 2;
                        cout << "CRITICAL HIT! ";
                    }
                    int finalDamage = itemDamage + critBonus;
                    target->info.health = target->info.health - finalDamage;
                    if (target->info.health < 0) {
                        target->info.health = 0;
                    }
                    cout << target->info.username << " menerima " << finalDamage << " damage! Sisa HP: ";
                    printHealthBar(target->info.health, target->info.maxHealth);
                    cout << "\n";
                }

                if (itemBroken) {
                    cout << "PERINGATAN: " << item->info.namaItem << " telah hancur (Durability 0) dan dihapus!\n";
                    deleteInventoryByID(attacker, idInv);
                }
            }
        }
    }
}

/* I.S. ListPlayer terdefinisi, idPlayer dan idInv terdefinisi
   F.S. Menambahkan jumlah item sebanyak qty dan menambah statistik timesCrafted atau timesMined */
void tambahStokItem(ListPlayer &LP, string idPlayer, string idInv, int qty, bool isCrafted) {
    adrPlayer P = searchPlayer(LP, idPlayer);
    if (P != nullptr && qty > 0) {
        adrInventory I = searchInventory(P, idInv);
        if (I != nullptr) {
            I->info.jumlah = I->info.jumlah + qty;
            if (isCrafted) {
                I->info.timesCrafted = I->info.timesCrafted + qty;
            } else {
                I->info.timesMined = I->info.timesMined + qty;
            }
            cout << "Berhasil menambah " << qty << " " << I->info.namaItem
                 << " ke inventory " << P->info.username << ".\n";
        } else {
            cout << "Item tidak ditemukan di inventory player.\n";
        }
    } else {
        cout << "Player tidak ditemukan atau jumlah tidak valid.\n";
    }
}

/* I.S. ListPlayer terdefinisi, idPlayer dan healPoint terdefinisi
   F.S. Menambah health Player sebesar healPoint tanpa melebihi maxHealth */
void healPlayer(ListPlayer &LP, string idPlayer, int healPoint) {
    adrPlayer P = searchPlayer(LP, idPlayer);
    if (P != nullptr && healPoint > 0) {
        P->info.health = P->info.health + healPoint;
        if (P->info.health > P->info.maxHealth) {
            P->info.health = P->info.maxHealth;
        }
        cout << P->info.username << " memulihkan HP! Kondisi sekarang: ";
        printHealthBar(P->info.health, P->info.maxHealth);
        cout << "\n";
    } else {
        cout << "Player tidak ditemukan.\n";
    }
}
