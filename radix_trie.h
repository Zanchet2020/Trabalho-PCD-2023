#ifndef RADIX_TRIE_H_
#define RADIX_TRIE_H_

#include <stdbool.h>

typedef struct Trie
{
    void ** children;
    bool marked;
} Trie;

Trie createTrie();

void deleteTrie();


#endif