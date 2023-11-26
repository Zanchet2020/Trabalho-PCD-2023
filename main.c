#define RADIX_TRIE 0

#if RADIX_TRIE
    #include "radix_trie.h"
#else
    #include "trie.h"
#endif

#include "register.h"
#include "bank.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    Bank * bank = createBank("banco.txt");

    int isRunning = 1;

    while (isRunning)
    {
        char selected;
        scanf("%c", &selected);
        switch (selected)
        {
        case '?':
        {
            char id[ID_LENGHT];
            scanf("%s", id);
            Register * reg = searchBank(bank, id);
            if(reg){
                printf("(%s|%s|%d)\n", reg->id, reg->name, reg->age);
            } else {
                printf("ID %s nao encontrado.\n", id);
            }
            break;
        }
        case '+':
        {    
            Register * reg = newRegister();
            scanf("%s", reg->id);
            //reading space
            getc(stdin);

            char name[NAME_LENGHT];
            char age[2];
            char aux = '\0';        

            //reading name and stopping on age
            int lenght = 0;
            for(;;lenght++){
                aux = getc(stdin);
                if(isdigit(aux)){
                    name[lenght-1] = '\0';
                    age[0] = aux;
                    aux = getc(stdin);
                    if(aux == '\n') break;
                    age[1] = aux;
                    break;
                }
                name[lenght] = aux;
            }
            reg->age = atoi(age);
            strcpy(reg->name, name);
            registerBank(bank, reg);
            printf("Inserido (%s|%s|%d)\n", reg->id, reg->name, reg->age);
            break;
        }
        case '-':
        {    
            char id[ID_LENGHT];
            scanf("%s", id);
            Register * reg = removeBank(bank, id);
            printf("Removido (%s|%s|%d)\n", reg->id, reg->name, reg->age);
            break;
        }
        case 'S':
        {
            saveBank(bank);
            printf("banco.txt salvo\n");
            break;
        }
        case 'P':
        {
            printBank(bank);
            break;
        }
        case 'F':
        {
            destroyBank(bank);
            isRunning = 0;
            break;
        }
        default:
            break;
        }
    }
    return 0;
}