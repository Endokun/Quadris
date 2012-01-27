#ifndef __TRIE_H__
#define __TRIE_H__
#include <string>

struct TrieNode {
    bool isWord;
    TrieNode *letters[26];
    TrieNode() {
        isWord = false;
         for ( int i = 0; i < 26; i += 1 ) {
             letters[i] = NULL;
         } // for
    }
}; // TrieNode

void releasememory(TrieNode *node);
void insert(TrieNode *node, std::string word);
void preloadshortcuts(TrieNode *node);
void printwords(TrieNode *node, std::string *result, std::string word);
std::string grabfullcommand(TrieNode *node, std::string shortcut);
bool checkifexists(TrieNode *node, std::string word);
#endif
