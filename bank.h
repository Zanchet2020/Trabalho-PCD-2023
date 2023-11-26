#ifndef BANCO_H_
#define BANCO_H_

#include "trie.h"
#include "register.h"

#include <stdio.h>

typedef struct {
    Trie * trie;
    char database_filename[100];
    FILE * database_fp;
    unsigned int numOfRegisters;
} Bank;

Bank * createBank(const char * file);

int saveBank(Bank * bank);

void destroyBank(Bank * bank);

void printBank(Bank * bank);

Register * searchBank(Bank * bank, char * id);

void registerBank(Bank * bank, Register * reg);

Register * removeBank(Bank * bank, char * id);

#endif