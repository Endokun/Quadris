#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include "square.h"
#include "window.h"

class Block {
   protected:
      char c; //Tells what type of block it is
      int orientation; //Determines the orientation of the block by 0, 90, 180, and 270
      int originx; //Coordinates of the origin of a block, used for rotations
      int originy;
      
   public:
      Xwindow *board; //Points to main board
   
      Xwindow *sidewindow; //Points to side window
      
      Block();
      
      Block(int lvl, char type, Xwindow *m, Xwindow *s, bool gs);
      
      ~Block();
      
      Square *pos[4]; //A pointer to an array of pointers to 4 Squares (maximum number of squares per block)
      
      int numsquares; //How many squares the block still contains, used for scoring

      int level; //Records the level of which the block appears in      

      bool graphicstate;
      
      int colour; //Keeps track of colour of the block
 
      virtual void left() = 0; //Moves the block to the left
      
      virtual void right() = 0; //Moves the block to the right
      
      virtual void down() = 0; //Moves block down
      
      virtual void shift() = 0; //Shifts the block for rotational purposes
      
      virtual void unshift() = 0; //Shifts the block back to its original position after rotation
      
      virtual void clockwise() = 0; //Rotates the block clockwise
      
      virtual void counterclockwise() = 0; //Rotates the block counterclockwise
      
      virtual bool checkleft() = 0; //Checks to see if there's any space below the block for it to go left
      
      virtual bool checkright() = 0; //Checks to see if there's any space below the block for it to go right
      
      virtual bool checkbelow() = 0; //Checks to see if there's any space below the block for it to go down
      
      virtual char blocktype() = 0; //Returns the type of block it is
      
      friend std::ostream& ::operator<<(std::ostream &out, const Block &b); //Prints out the block
};

class I : public Block {
   public:
      I(int lvl, Xwindow *m, Xwindow *s, bool gs);
      ~I();
      void left();
      void right();
      void down();
      void shift();
      void unshift();
      void clockwise();
      void counterclockwise();
      bool checkleft();
      bool checkright();
      bool checkbelow();
      char blocktype();
};

class J : public Block {
   public:
      J(int lvl, Xwindow *m, Xwindow *s, bool gs);
      ~J();
      void left();
      void right();
      void down();
      void shift();
      void unshift();
      void clockwise();
      void counterclockwise();
      bool checkleft();
      bool checkright();
      bool checkbelow();
      char blocktype();
};

class L : public Block {
   public:
      L(int lvl, Xwindow *m, Xwindow *s, bool gs);
      ~L();
      void left();
      void right();
      void down();
      void shift();
      void unshift();
      void clockwise();
      void counterclockwise();
      bool checkleft();
      bool checkright();
      bool checkbelow();
      char blocktype();
};

class O : public Block {
   public:
      O(int lvl, Xwindow *m, Xwindow *s, bool gs);
      ~O();
      void left();
      void right();
      void down();
      void shift();
      void unshift();
      void clockwise();
      void counterclockwise();
      bool checkleft();
      bool checkright();
      bool checkbelow();
      char blocktype();
};

class S : public Block {
   public:
      S(int lvl, Xwindow *m, Xwindow *s, bool gs);
      ~S();
      void left();
      void right();
      void down();
      void shift();
      void unshift();
      void clockwise();
      void counterclockwise();
      bool checkleft();
      bool checkright();
      bool checkbelow();
      char blocktype();
};

class Z : public Block {
   public:
      Z(int lvl, Xwindow *m, Xwindow *s, bool gs);
      ~Z();
      void left();
      void right();
      void down();
      void shift();
      void unshift();
      void clockwise();
      void counterclockwise();
      bool checkleft();
      bool checkright();
      bool checkbelow();
      char blocktype();
};

class T : public Block {
   public:
      T(int lvl, Xwindow *m, Xwindow *s, bool gs);
      ~T();
      void left();
      void right();
      void down();
      void shift();
      void unshift();
      void clockwise();
      void counterclockwise();
      bool checkleft();
      bool checkright();
      bool checkbelow();
      char blocktype();
};
    
#endif
