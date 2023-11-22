#ifndef TRIE_H_
#define TRIE_H_

#include <stdbool.h>

typedef struct Trie
{
    struct Trie * children[26];
    void * content;
} Trie;

Trie * createTrie();

void destroyTrie(Trie * trie);

void * removeTrie(Trie * trie, char * word);

void insertTrie(Trie * trie, char * word, void * content);

void * searchTrie(Trie * trie, char * word);

#endif