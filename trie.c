#include "trie.h"

#include <stdlib.h>

Trie * createTrie(){
    Trie * trie = (Trie*)malloc(sizeof(Trie));
    trie->content = NULL;
    for(int i = 0; i < 26; i++){
        trie->children[i] = NULL;
    }
    return trie;
}


void destroyTrie(Trie * trie){
    // Destroy the whole Trie and FREES THE CONTENT MEMORY
    // Calling this function makes you lose all the data that is allocated in the data structure
    if(trie == NULL){
        return;
    }
    for(int i = 0; i < 26; i++){
        destroyTrie(trie->children[i]);
    }
    if(trie->content) free (trie->content);
    free(trie);
}

void insertTrie(Trie * trie, char * word, void * content){
    // Inserts some content into the Trie
    if(word[1] == '\0'){
        trie->content = content;
        return;
    }
    unsigned int index = word[0] - 'a';
    
    if(trie->children[index] == NULL){
        trie->children[index] = createTrie();
    }
    insertTrie(trie->children[index], word + 1, content);
    return;
}

void * removeTrie(Trie * trie, char * word){
    // Removes key from Trie but DOES NOT FREE THE CONTENT MEMORY
    // Freeing the content memory is the user's responsability
    unsigned int index = word[0] - 'a';
    if(trie->children[index] == NULL){
        if(word[1] == '\0'){
            int isNodeChildless = 1;
            for(int i; i < 26; i++){
                isNodeChildless = !trie->children[i] == NULL;
            }
            if(isNodeChildless){
                void * temp_content = trie->content;
                free(trie);
                return temp_content;
            }
            return trie->content;
        } else return NULL;
    } else if (word[1] == '\0'){
        void * temp_content = trie->content;
        trie->content = NULL;
        return temp_content;
    } else {
        return removeTrie(trie->children[index], word + 1);
    }
}

void * searchTrie(Trie * trie, char * word){
    // Returns NULL if key doesn't exist
    // Returns pointer to content in case it exists
    unsigned int index = word[0] - 'a';
    if(trie->children[index] == NULL){
        if(word[1] == '\0'){
            return trie->content;
        } else return NULL;
    } else if (word[1] == '\0'){
        return trie->content;
    } else {
        return searchTrie(trie->children[index], word + 1);
    }
}