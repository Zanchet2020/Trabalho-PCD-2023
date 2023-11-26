#include "register.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Register * newRegister(){
    Register * new = (Register*)malloc(sizeof(Register));
    new->age = 0;
    return new;
}

void deleteRegister(Register * reg){
    if(reg->id) free(reg->id);
    if(reg->name) free(reg->name);
    free(reg);
}

unsigned int readBank(FILE * fs, Trie * trie){
    unsigned int NumOfReg = 0;
    fscanf(fs, "%d", &NumOfReg);

    for(int i; i < NumOfReg; i ++){
        Register * reg = newRegister();
        // reading id
        fscanf(fs, "%s", reg->id);
        // temp array to read the whole line
        
        char id[ID_LENGHT];
        char name[NAME_LENGHT];
        char age[2];
        char aux = '\0';
        for(int i; aux != ' '; i++){
            aux = getc(fs);
            if(aux == ' '){
                id[i] = '\0';
                break;
            }
            id[i] = aux;
        }
        

        int lenght = 0;
        for(;;lenght++){
            aux = getc(fs);
            if(isdigit(aux)){
                name[lenght] = '\0';
                age[0] = aux;
                aux = getc(fs);
                if(aux == '\n') break;
                age[1] = aux;
                break;
            }
            name[lenght] = aux;
        }
        reg->age = atoi(age);
        strcpy(reg->id, id);
        strcpy(reg->name, name);
        insertTrie(trie, reg->id, reg);
    }

    return NumOfReg;
}