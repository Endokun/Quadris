#include <iostream>
#include <fstream>
#include <iomanip>
#include "trie.h"
using namespace std;

//Releases all the memory
void releasememory(TrieNode *node) {
   for(int i = 0; i < 26; i++) {
      if(node->letters[i] != NULL)
         releasememory(node->letters[i]);
   }
   delete node;
}

//Adds a name
void insert(TrieNode *node, string word) {
   TrieNode *tempnode = node; //Creates a temporary node to traverse down the tree
   int lengthofword = word.length(); //Stores length of word
   int n = 0;
   for(int i = 0; i < lengthofword; i++) { //Goes through the TrieNodes
      n = word[i] - 'a';
      if(tempnode->letters[n] == NULL) {
         tempnode->letters[n] = new TrieNode;
         tempnode = tempnode->letters[n];
      }
      else {
         tempnode = tempnode->letters[n];
      }
   }
   tempnode->isWord = true;
}

//Actively goes through all the children that aren't NULL and accumulates the words into a string
void printwords(TrieNode *node, string *result, string word) {
   if(node->isWord)
      *result = word;
   for(int i = 0; i < 26; i++) {
      if(node->letters[i] != NULL) {
         char letter = 'a' + i;
         printwords(node->letters[i], result, word + letter); //Recursive
      }
   }
}

//Takes the shortcut and get the name for the full command
string grabfullcommand(TrieNode *node, string word) {
   string command = word;
   string *result = &command;
   TrieNode *tempnode = node;
   int lengthofword = word.length();
   int n = 0;
   for(int i = 0; i < lengthofword; i++) { //Gets to the position where the shortcut ends
      n = word[i] - 'a';
      tempnode = tempnode->letters[n]; //Goes further down the tree
   }
   for(int i = 0; i < 26; i++) { //Goes through all the children to return the full command
      if(tempnode->letters[i] != NULL) {
         char letter = 'a' + i;
         printwords(tempnode->letters[i], result, word + letter);
      }
   }
   return command;
}

//Checks if the shortcut command is valid
bool checkifexists(TrieNode *node, string word) {
   TrieNode *tempnode = node;
   int numpaths = 0; //Used to make sure the shortcut entered only has one possible path
   int lengthofword = word.length();
   if(lengthofword > 26 || lengthofword < 0)
      return false;
   int n = 0;
   for(int i = 0; i < lengthofword; i++) {
      if(tempnode->letters[i] != NULL)
         numpaths++;
   }
   if(1) {
      for(int i = 0; i < lengthofword; i++) {
         n = word[i] - 'a';
         if(tempnode->letters[n] == NULL)
            return false; //Since the letter is NULL, it means the given word does not exist in the tree
         else
            tempnode = tempnode->letters[n]; //Goes further down the tree
      }
      if(tempnode->isWord) //If the word exists, return true
         return true;
      else
         return false;
   }
   else
      return false;
}
