#ifndef __SQUARE_H__
#define __SQUARE_H__
#include <iostream>

class Block; //Forward declaration

class Square {
      int xcord; //What column is it on
      int ycord; //What row is it on
      int level; //Level the square contains
      char type; //What type of block it is
      bool state; //If the square exists, used for the board
   public:
      Block *bp; //Pointer to the block the square belongs to
      
      Square(); //Default constructor

      Square(Block *b);
      
      ~Square();

      void draw(); //Draws squares
      
      void undraw(); //Undraws squares

      void initsquare(int x, int y, int l, char t); //Sets the coordinates for the square as well as stores the level
                                                    //the square appears in and what type of block it belongs to
      
      void changecord(int a, int b); //Gives coordinates to change the position of the square
      
      void attachbp(Block *b); //Assigns a square pointing to a block
      
      void detachbp(); //Unassigns the block
      
      int xpos(); //Returns the value of xcord
      
      int ypos(); //Returns the vale of ycord
      
      void statechange(bool s); //Changes whether or not the Square exists or not
      
      void typechange(char c); //Changes the type of square it is
      
      void levelchange(int l); //Changes the level
      
      bool currentstate(); //Returns the current state of the Square
      
      char currenttype(); //Returns the type of the Square
      
      int currentlevel(); //Returns the Square's level
      
      friend std::ostream& ::operator<<(std::ostream &out, Square s); //Prints out the square
};

#endif
