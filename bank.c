#include "bank.h"
#include "trie.h"
#include "register.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>



Bank * createBank(const char * file){
    Bank * bank = (Bank*)malloc(sizeof(Bank));
    strcpy_s(bank->database_filename, 100*sizeof(char), file);
    bank->trie = createTrie();
    bank->numOfRegisters = 0;
    bank->database_fp = fopen(bank->database_filename, "r+");

    fscanf(bank->database_fp, "%d", &bank->numOfRegisters);

    for(int i = 0; i < bank->numOfRegisters; i ++){
        Register * reg = newRegister();
        // reading id
        fscanf(bank->database_fp, "%s", reg->id);
        // reading space
        getc(bank->database_fp);

        char name[NAME_LENGHT];
        char age[2];
        char aux = '\0';        

        int lenght = 0;
        for(;;lenght++){
            aux = getc(bank->database_fp);
            if(isdigit(aux)){
                name[lenght-1] = '\0';
                age[0] = aux;
                aux = getc(bank->database_fp);
                if(aux == '\n') break;
                age[1] = aux;
                break;
            }
            name[lenght] = aux;
        }
        reg->age = atoi(age);
        strcpy(reg->name, name);
        insertTrie(bank->trie, reg->id, reg);
    }
    return bank;
}

void printTrie(FILE * out, Trie * trie){
    if(trie->content != NULL){
        Register reg = *(Register *)trie->content;
        if(out == stdout) fprintf(out, "(%s|%s|%d)\n", reg.id, reg.name, reg.age);
        else fprintf(out, "%s %s %d\n", reg.id, reg.name, reg.age);
    }
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(trie->children[i] != NULL){
            printTrie(out, trie->children[i]);
        }
    }
}

void printBank(Bank * bank){
    printTrie(stdout, bank->trie);
}

int saveBank(Bank * bank){
    bank->database_fp = fopen(bank->database_filename, "w+");
    if(bank->database_fp == NULL) {
        printf("Error code: %s\n", strerror(errno));
    }
    fprintf(bank->database_fp, "%d\n", bank->numOfRegisters);
    printTrie(bank->database_fp, bank->trie);
    fclose(bank->database_fp);
    bank->database_fp = fopen(bank->database_filename, "r+");
    return 0;
}

void destroyBank(Bank * bank){
    destroyTrie(bank->trie, NULL);
    fclose(bank->database_fp);
    free(bank);
}

Register * searchBank(Bank * bank, char * id){
    return (Register*)searchTrie(bank->trie, id);
}

void registerBank(Bank * bank, Register * reg){
    insertTrie(bank->trie, reg->id, reg);
    bank->numOfRegisters++;
}

Register * removeBank(Bank * bank, char * id){
    bank->numOfRegisters--;
    return (Register*)removeTrie(bank->trie, id);
}

