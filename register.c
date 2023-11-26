#include "register.h"

#include <stdlib.h>

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

