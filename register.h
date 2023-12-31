#ifndef CADASTRO_H_
#define CADASTRO_H_

#include "trie.h"

#include <stdio.h>

#define FILE_NAME "banco.txt"
#define ID_LENGHT 30
#define NAME_LENGHT 1000


typedef struct
{
    char id[ID_LENGHT];
    char name[NAME_LENGHT];
    unsigned int age;
} Register;

Register * newRegister();

void deleteRegister(Register * reg);

#endif