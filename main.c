#define RADIX_TRIE 0

#if RADIX_TRIE
    #include "radix_trie.h"
#else
    #include "trie.h"
#endif

#include "register.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int main(){
    unsigned int NumOfRegisters;
    FILE * fs = fopen("banco.txt", "rw");
    Trie * trie = createTrie();

    readBank(fs, trie);

    
    destroyTrie(trie);
    fclose(fs);
    
    return 0;
}