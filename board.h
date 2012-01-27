#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include "block.h" 
#include "square.h"
#include "window.h"
#include "PRNG.h"
#include "trie.h"

class Board {
      Square board[18][10]; //Creates 18 x 10 grid of Squares
      int level; //The level the player is currently on;
      int highscore; //Keeps track of the player's most high score
      int currentscore; //Keeps track of the current score of the player
   public:
      bool graphicstate; //Whether graphics are active or not
      
      Board(); //Constructor
      
      Xwindow *boardwindow; //Display
      
      ~Board(); //Destructor
      
      Block *createblock(char type, Xwindow *mainboard, Xwindow *sidewindow); //Creates a block
      
      void boardadd(Board *B, Block *b); //Updates the board and makes the square either on or off
      
      void boardremove(Board *B, Block *b); //Removes the block from the board and makes those squares off
      
      char nextblock(std::istream &blocktype); //Dictates what the next block should be
      
      PRNG newp; // For random generator of blocks
      void Change(int n);
      
      void move(std::string command, Block *b); //Moves a block based on input
      
      bool checkcollision(Board *B, Block *b); //Makes sure that the block is not currently over existing blocks, mainly used to check rotation
      
      bool checkleftcollision(Board *B, Block *b); //Makes sure that blocks don't go through each other or the left wall
      
      bool checkrightcollision(Board *B, Block *b); //Makes sure that blocks don't go through each other or the right wall
      
      bool checkbelowcollision(Board *B, Block *b); //Makes sure that blocks don't go through each other or the ground
      
      bool checkline(int n); //Checks if row n is filled
      
      void clearline(); //Removes all filled lines and calculates score
      
      void lineshift(int n); //Shifts all the lines above the cleared line down 1 square
      
      void restart(); //Restarts the game
            
      int levelup(); //Increases level
      
      int leveldown(); //Decreases level
      
      void graphicsstate(bool state); //Determines whether graphics are turned on or off
      
      void assignscore(int hs); //Assigns highscore
      
      int returnscore(); //Returns highscore
      
      friend std::ostream& ::operator<<(std::ostream &out, Board &B); //Prints out the board state
};

void executecommands(std::istream &input, Board *B, TrieNode *node, Xwindow *boardwindow, Xwindow *sidewindow, bool graphicstate); //Executes commands from user

#endif
